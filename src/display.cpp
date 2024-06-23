#include <display.h>

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <lcd_esp.h>

#define BG_LIGHT 32
#define SSD_SS SS
#define SSD_MISO MISO
#define SSD_MOSI MOSI
#define SSD_SCK SCK
#define RESET_PIN 25

static RW1073 lcd(SSD_SS, SSD_MISO, SSD_MOSI, SSD_SCK, RESET_PIN);

/**
 * Initialize the display with base settings
 * @return void
 */
void init_display() {
    pinMode(BG_LIGHT, OUTPUT);
    digitalWrite(BG_LIGHT, HIGH);

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
void set_display_row(int x, int y, char *content) {
    lcd.setPos(x, y);
    lcd.printf(content);
}
