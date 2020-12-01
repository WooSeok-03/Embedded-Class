#include "servo.h"

#define SERVO_PIN 12

void servo_init()
{
  pinMode(SERVO_PIN, OUTPUT);
  
  TCCR3A = 0x03;
  TCCR3B = 0x0B;
  OCR3A = 1024 - 625 + 175;
  TCNT3 = 1024 - 625;
  //TIMSK3 = 0x00;
}


volatile int servo_OVF_count = 0;
volatile int servo_duty = 175;


ISR(TIMER3_COMPA_vect) {
  if (servo_OVF_count == 0)
  {
    digitalWrite(SERVO_PIN, LOW);
  }
}
ISR(TIMER3_OVF_vect) {
  servo_OVF_count++;
  if (servo_OVF_count == 8)
  {
    digitalWrite(SERVO_PIN, HIGH);
    servo_OVF_count = 0;
    servo_duty += 4;
    if (servo_duty >= 575)
    {
      servo_duty = 175;
    }
    OCR3A = 1024 - 625 + servo_duty;
    TCNT3 = 1024 - 625;
  }
}
