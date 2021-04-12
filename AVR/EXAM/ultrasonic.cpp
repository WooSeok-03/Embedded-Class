#include "ultrasonic.h"

unsigned long echo_time = 0;
unsigned int diff_time = 0;
unsigned long ultrasonic_millis = 0;
float ultrasonic_distance = 0;

void ultrasonicInit() {
  DDRG |= TRIG_PIN;
  DDRE &= ~ECHO_PIN;

  EICRB |= 0x01;
  EIMSK |= 0x10;
}

void ultrasonicTrigger(unsigned long c_millis) {
  if (c_millis - ultrasonic_millis > 50) {
    PORTG |= TRIG_PIN;
    delayMicroseconds(10);
    PORTG &= ~TRIG_PIN;
  }
}

int getDistance() {
  return ultrasonic_distance;
}

SIGNAL(INT4_vect) {
  if (PINE & ECHO_PIN) // rising edge
  {
    echo_time = micros();
  }
  else
  {
    diff_time = micros() - echo_time;
    ultrasonic_distance = diff_time * 0.017;
  }
}
