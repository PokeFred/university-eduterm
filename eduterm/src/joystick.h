#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

/**
 * Initialize the joystick with base settings
 * @return void
 */
void init_joystick();

/**
 * Check if any joystick button is updated
 * @return bool
 */
bool isJoyStickUpdate();

/**
 * Check if joystick button is pressed by pin and status
 * @return bool
 */
bool isJoyStickButtonPressed(uint8_t pin, bool *status);

/**
 * Check if the top joystick button is pressed
 * @return bool
 */
bool isTopJoyStickPressed();

/**
 * Check if the left joystick button is pressed
 * @return bool
 */
bool isLeftJoyStickPressed();

/**
 * Check if the right joystick button is pressed
 * @return bool
 */
bool isRightJoyStickPressed();

/**
 * Check if the bottom joystick button is pressed
 * @return bool
 */
bool isBottomJoyStickPressed();

#endif
