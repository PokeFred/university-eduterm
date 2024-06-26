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

void setup() {
    delay(1536);
    Serial.begin(115200);
    init_status_led();
    init_display();
    init_buzzer();

    init_joystick();
    init_encoder();

    for (int i = 0; i < 4; i++) {
        //char buffer[1];
        //itoa(i, buffer, 1);
        //char *content = strcat("Zeile ", buffer);

        set_display_row(0, i, "Zeile", i);
    }

    toggle_red_status_led();
}

void loop() {
    if (isTopJoyStickPressed()) {
        toggle_green_status_led();
    } else if (isLeftJoyStickPressed()) {
        //toggle_green_status_led();
    } else if (isRightJoyStickPressed()) {
        //toggle_green_status_led();
    } else if (isBottomJoyStickPressed()) {
        //toggle_green_status_led();
    } else {
        toggle_red_status_led();
    }

    delay(100);
}
