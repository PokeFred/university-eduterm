#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void init_display();
void set_display_row(int x, int y, char *content);

#endif
