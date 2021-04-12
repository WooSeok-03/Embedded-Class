#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"
#include "exti.h"

void ultrasonic_init(int int_pin_num, char trigger_pin_num);
void ultrasonic_trigger();
void ultrasonic_callback_flag_clear();
char ultrasonic_callback(float *distance);
void ultrasonic_ISR();

#endif
