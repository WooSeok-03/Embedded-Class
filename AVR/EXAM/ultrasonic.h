#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

#define TRIG_PIN 0x20   //PG5
#define ECHO_PIN 0x10   //PE4

void ultrasonicInit();
void ultrasonicTrigger(unsigned long millis);
int getDistance();

#endif
