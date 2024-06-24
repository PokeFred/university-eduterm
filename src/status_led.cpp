#include <status_led.h>

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 27
#define NUMPIXELS 1
#define BRIGHTNESS 50

static Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

/**
 * Initialize the status LED with base settings
 * @return void
 */
void init_status_led() {
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.show();
}

/**
 * Turn on the status LED with an specified RGB-Color
 * @param int red
 * @param int green
 * @param int blue
 * @return void
 */
void toggle_status_led(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t pixelIndex = 0;

    strip.setPixelColor(pixelIndex, red, green, blue);
    strip.show();
}

/**
 * Turn on the status LED with an specified RGBW-Color
 * @param int red
 * @param int green
 * @param int blue
 * @param int white
 * @return void
 */
void toggle_status_led(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    uint8_t pixelIndex = 0;

    strip.setPixelColor(pixelIndex, red, green, blue, white);
    strip.show();
}

/**
 * Turn on the status LED with black color
 * @return void
 */
void toggle_black_status_led() {
    toggle_status_led(0, 0, 0);
}

/**
 * Turn on the status LED with red color
 * @return void
 */
void toggle_red_status_led() {
    toggle_status_led(255, 0, 0);
}

/**
 * Turn on the status LED with green color
 * @return void
 */
void toggle_green_status_led() {
    toggle_status_led(0, 255, 0);
}
