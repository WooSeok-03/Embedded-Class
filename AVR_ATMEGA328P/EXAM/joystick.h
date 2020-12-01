#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"

#define JOY_BUTTON 11

#define AD_0 0
#define AD_1 1
#define AD_2 2
#define AD_3 3
#define AD_4 4
#define AD_5 5

void adc_init();
unsigned short analog_read(char channel);

#endif
