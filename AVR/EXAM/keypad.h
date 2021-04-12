#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"

#define COL 37
#define ROW 35

void keypadInit();
void keyInput(unsigned long c_millis);
int getInputNumber();

#endif
