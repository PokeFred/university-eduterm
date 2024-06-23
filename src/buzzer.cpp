#include <Arduino.h>

#define BUZZER 33

/**
 * Initialize the buzzer with base settings
 * @return void
 */
void init_buzzer() {
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);
}

/**
 * Turn on the buzzer for the specified duration
 * @param int ms
 * @return void
 */
void buzzer_signal(int ms) {
    ms = (ms <= 2000) ? ms : 2000;
    digitalWrite(BUZZER, HIGH);
    delay(ms);
    digitalWrite(BUZZER, LOW);
}
