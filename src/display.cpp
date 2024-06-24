#include <display.h>

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <lcd_esp.h>

#define INPUT_PIN 32
#define RESET_PIN 25
#define SSD_SS SS
#define SSD_MISO MISO
#define SSD_MOSI MOSI
#define SSD_SCK SCK

static RW1073 lcd(SSD_SS, SSD_MISO, SSD_MOSI, SSD_SCK, RESET_PIN);

/**
 * Initialize the display with base settings
 * @return void
 */
void init_display() {
    pinMode(INPUT_PIN, OUTPUT);
    digitalWrite(INPUT_PIN, HIGH);

    lcd.begin(HD44780::R4, HD44780::C20);
    lcd.cursorOff();
    lcd.homePos();
}

/**
 * Set the display row with the specified content
 * @param int x
 * @param int y
 * @param char *content
 * @return void
 */
void set_display_row(uint8_t x, uint8_t y, const char *content...) {
    lcd.setPos(x, y);
    lcd.printf(content);
}

// TODO clear method
