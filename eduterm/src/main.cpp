#include <Arduino.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>
#include <ESP32Encoder.h>
#include <lcd_esp.h>
#include <monitor.h>
#include <stdlib.h>

#include <display.h>
#include <buzzer.h>
#include <status_led.h>
#include <joystick.h>

#include "../../server/src/dataframe.h"

static const char *SSID = "";
static const char *PASSWORD = "";
static WiFiUDP udp;

// RW1073 Display settings
constexpr uint8_t BG_LIGHT = 32;
constexpr uint8_t SSD_SS = SS;
constexpr uint8_t SSD_MISO = MISO;
constexpr uint8_t SSD_MOSI = MOSI;
constexpr uint8_t SSD_SCK = SCK;
constexpr uint8_t RESET_PIN = 25;
static RW1073 lcd(SSD_SS, SSD_MISO, SSD_MOSI, SSD_SCK, RESET_PIN);
constexpr uint8_t CHAR_SMILEY = 0;
constexpr uint8_t CHAR_FROWNIE = 1;

// NeoPixel status RGB LED settings
constexpr int16_t LED_PIN = 27;    // Which pin is connected to the NeoPixel
constexpr uint16_t NUMPIXELS = 1;  // Number of connected RGB LEDS
static Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
static uint32_t COL_BLK;
static uint32_t COL_RED;
static uint32_t COL_GRN;

// Joystick settings
constexpr uint8_t switchU = 34;
constexpr uint8_t switchR = 35;
constexpr uint8_t switchD = 12;
constexpr uint8_t switchL = 0;
constexpr uint8_t joystick[4] = {switchU, switchR, switchD, switchL};
static uint8_t js_state;
#define JS_UP    ((js_state & 1<<0) ? false : true)
#define JS_RIGHT ((js_state & 1<<1) ? false : true)
#define JS_DOWN  ((js_state & 1<<2) ? false : true)
#define JS_LEFT  ((js_state & 1<<3) ? false : true)

// Rotary Encoder settings
constexpr int ENC_A = 17;
constexpr int ENC_B = 16;
constexpr uint8_t ENC_SW = 15;
static ESP32Encoder encoder;
static Bounce encButton = Bounce();
static int64_t encoder_count;

void init_encoder() {
    encoder.attachSingleEdge(ENC_A, ENC_B);
    encoder.clearCount();
    encButton.attach(ENC_SW, INPUT); // TODO input pin rename
    encButton.interval(5);  // Debounce intervall in ms
    pinMode(ENC_SW, INPUT);
}

/**
void init_joystick() {
    pinMode(switchU, INPUT);
    pinMode(switchR, INPUT);
    pinMode(switchD, INPUT_PULLUP);
    pinMode(switchL, INPUT);
    delay(100);
    for (int i = 0; i < 4; i++) {
        js_state |= digitalRead(joystick[i]) << i;
    }
}
*/

void init_wifi() {
    WiFiClass::mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    bool led_state = true;
    for (int i = 1; true; i++) {
        if (WiFiClass::status() == WL_CONNECTED) break;
        delay(500);

        if (i % 10) {
            Serial.print(F("."));
        } else {
            Serial.printf("(%is)", i / 2);
        }

        led_state = !led_state;

        if (led_state) {
            toggle_red_status_led();
        } else {
            toggle_black_status_led();
        }
    }

    Serial.printf("Connected to Wi-Fi '%s'\n", SSID);
    Serial.print(F("(now I am client '"));
    Serial.print(WiFi.localIP());
    Serial.println(F("')\n"));

    toggle_green_status_led();
    randomSeed(micros());

    if (udp.begin(MY_UDP_PORT) == 0) {
        toggle_red_status_led();
        buzzer_signal(500);
        delay(5000);
        ESP.restart();
    }

    set_display_row(0, 0, " - E d u T e r m -  ");
    set_display_row(0, 1, "Now my IP address is");
    set_display_row(0, 2, WiFi.localIP().toString().c_str());
    set_display_row(0, 3, "(waiting for data..)");
}

void setup() {
    delay(1536);
    Serial.begin(115200);
    init_status_led();
    init_display();
    init_buzzer();

    init_wifi();
    init_joystick();
    init_encoder();

    for (int i = 0; i < 4; i++) {
        //char buffer[1];
        //itoa(i, buffer, 1);
        //char *content = strcat("Zeile ", buffer);

        //set_display_row(0, i, "Zeile", i);
    }

    //toggle_red_status_led();
}

int receive_job_msg(void *message, int msg_size) {
    int received_size = 0;
    bzero(message, msg_size);
    int packet_size = udp.parsePacket();
    if (packet_size) {
        IPAddress remoteIp = udp.remoteIP();
        if (packet_size == msg_size) {
            received_size = udp.read((unsigned char *) message, msg_size);
            if (received_size == msg_size) {
                Serial.println(F("Datagram of expected size has been read"));
                buzzer_signal(40);
                delay(50);
                buzzer_signal(40);
                Serial.printf("%d\n", received_size);
            } else {
                Serial.println(F("Failure: Datagram has been partially read"));
                received_size = 0;
            }
        }
        udp.flush();
    }
    return received_size;
}

#define MAX_PAGES 10
page_t pages[MAX_PAGES];
int current_page = 0;

void loop() {
    dataframe frame;
    if (receive_job_msg(&frame, sizeof(frame)) == sizeof(frame)) {
        if (frame.pageNumber >= 0 && frame.pageNumber < MAX_PAGES - 1){
            memcpy(pages[frame.pageNumber], frame.pageContent, sizeof(page_t));
        }

        Serial.printf("Received page %d\n", frame.pageNumber);
        Serial.printf("Page 0: %s\n", frame.pageContent[0]);
        Serial.printf("Page 1: %s\n", frame.pageContent[1]);
        Serial.printf("Page 2: %s\n", frame.pageContent[2]);
        Serial.printf("Page 3: %s\n", frame.pageContent[3]);

        //Serial.printf("Current page: %d\n", current_page);
        //Serial.printf("Page 0: %s\n", pages[current_page][0]);
        //Serial.printf("Page 1: %s\n", pages[current_page][1]);
        //Serial.printf("Page 2: %s\n", pages[current_page][2]);
        //Serial.printf("Page 3: %s\n", pages[current_page][3]);
        //Serial.printf("--------------------\n");
    }

    //set_display_row(0, 0, pages[current_page][0]);
    //set_display_row(0, 1, pages[current_page][1]);
    //set_display_row(0, 2, pages[current_page][2]);
    //set_display_row(0, 3, pages[current_page][3]);

    /*
    if (isTopJoyStickPressed()) {
        //toggle_green_status_led();
    } else if (isLeftJoyStickPressed()) {
        //toggle_green_status_led();
    } else if (isRightJoyStickPressed()) {
        //toggle_green_status_led();
    } else if (isBottomJoyStickPressed()) {
        //toggle_green_status_led();
    } else {
        //toggle_red_status_led();
    }

    delay(100);
    */
}
