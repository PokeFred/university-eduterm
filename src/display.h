#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

/**
 * Initialize the display with base settings
 * @return void
 */
void init_display();

/**
 * Set the display row with the specified content
 * @param int x
 * @param int y
 * @param char *content
 * @return void
 */
void set_display_row(uint8_t x, uint8_t y, const char *content...);

#endif
