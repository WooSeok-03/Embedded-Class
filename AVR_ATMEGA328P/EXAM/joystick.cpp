#include "joystick.h"

void adc_init()
{
  ADMUX |= 0x40;
  ADCSRA = 0x87;
  ADCSRB = 0x00;
}

unsigned short analog_read(char channel)
{
  unsigned short adc_value = 0;
  
  ADMUX &= ~0x0f;
  ADMUX |= channel;

  ADCSRA |= 0x40;

  while(!(ADCSRA & 0x10));
  adc_value = ADC;

  return adc_value;
}
