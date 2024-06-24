#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

/**
 * Initialize the buzzer with base settings
 * @return void
 */
void init_buzzer();

/**
 * Turn on the buzzer for the specified duration
 * @param int ms
 * @return void
 */
void buzzer_signal(uint32_t ms);

#endif
