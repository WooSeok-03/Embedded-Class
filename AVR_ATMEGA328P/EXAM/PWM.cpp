#include "PWM.h"


int led_PWM_count = 0;
int led_PWM_duty = 1;

void PWM_setup()
{
  DDRB |= LED;
  
  TCCR1A = 0x00;
  TCCR1B = 0x0B; //count 125개면 1ms
  OCR1A = 10;
}

ISR(TIMER1_COMPA_vect) {
  led_PWM_count++;
  if(led_PWM_count == led_PWM_duty)
  {
    PORTB &= ~(LED);
  }
  if(led_PWM_count == 100)
  {
    PORTB |= LED;
    led_PWM_count = 0;
    led_PWM_duty++;
    if(led_PWM_duty == 100)
    {
      led_PWM_duty = 0;
    }
  }
}
