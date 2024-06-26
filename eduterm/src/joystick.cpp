#include <joystick.h>

#include <Arduino.h>

#define TOP_BUTTON 34
#define LEFT_BUTTON 0
#define RIGHT_BUTTON 35
#define BOTTOM_BUTTON 12

bool topJoyStickPressed = false;
bool leftJoyStickPressed = false;
bool rightJoyStickPressed = false;
bool bottomJoyStickPressed = false;

/**
 * Initialize the joystick with base settings
 * @return void
 */
void init_joystick() {
    pinMode(TOP_BUTTON, INPUT);
    pinMode(LEFT_BUTTON, INPUT);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(BOTTOM_BUTTON, INPUT);
}

/**
 * Check if any joystick button is updated
 * @return bool
 */
bool isJoyStickUpdate() {
    return isTopJoyStickPressed() || isLeftJoyStickPressed() || isRightJoyStickPressed() || isBottomJoyStickPressed();
}

/**
 * Check if joystick button is pressed by pin and status
 * @return bool
 */
bool isJoyStickButtonPressed(uint8_t pin, bool *status) {
    bool state = digitalRead(pin) == LOW;
    return state;

    // TODO fix this

    if (state && *status) {
        // pressed and pressed before
        return false;
    } else if (state && !*status) {
        // pressed and not pressed before
        *status = true;
        return true;
    } else if (!state && *status) {
        // not pressed and pressed before
        *status = false;
        return false;
    } else {
        // not pressed and not pressed before
        return false;
    }
}

/**
 * Check if the top joystick button is pressed
 * @return bool
 */
bool isTopJoyStickPressed() {
    return isJoyStickButtonPressed(TOP_BUTTON, &topJoyStickPressed);
}

/**
 * Check if the left joystick button is pressed
 * @return bool
 */
bool isLeftJoyStickPressed() {
    return isJoyStickButtonPressed(LEFT_BUTTON, &leftJoyStickPressed);
}

/**
 * Check if the right joystick button is pressed
 * @return bool
 */
bool isRightJoyStickPressed() {
    return isJoyStickButtonPressed(RIGHT_BUTTON, &rightJoyStickPressed);
}

/**
 * Check if the bottom joystick button is pressed
 * @return bool
 */
bool isBottomJoyStickPressed() {
    return isJoyStickButtonPressed(BOTTOM_BUTTON, &bottomJoyStickPressed);
}
