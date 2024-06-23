#include <status_led.h>

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
 * Turn on the status LED with the specified color
 * @param int red
 * @param int green
 * @param int blue
 * @return void
 */
void toggle_status_led(int red, int green, int blue) {
    strip.setPixelColor(0, Adafruit_NeoPixel::Color(red, green, blue));
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
