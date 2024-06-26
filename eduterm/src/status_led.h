#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <Arduino.h>

/**
 * Initialize the status LED with base settings
 * @return void
 */
void init_status_led();

/**
 * Turn on the status LED with an specified RGB-Color
 * @param int red
 * @param int green
 * @param int blue
 * @return void
 */
void toggle_status_led(uint8_t red, uint8_t green, uint8_t blue);

/**
 * Turn on the status LED with an specified RGBW-Color
 * @param int red
 * @param int green
 * @param int blue
 * @param int white
 * @return void
 */
void toggle_status_led(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

/**
 * Turn on the status LED with black color
 * @return void
 */
void toggle_black_status_led();

/**
 * Turn on the status LED with red color
 * @return void
 */
void toggle_red_status_led();

/**
 * Turn on the status LED with green color
 * @return void
 */
void toggle_green_status_led();

#endif
