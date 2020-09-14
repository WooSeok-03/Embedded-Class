#include "exti.h"

void (*ISR_func_ptr_0)();
void (*ISR_func_ptr_1)();

void exti_init(char int_num, char mode, void (*ISR_ptr)())
{
  char int_pin_num = 2 + int_num;
  
  if(int_num == 0)
  {
    ISR_func_ptr_0 = ISR_ptr;
  }
  else if(int_num == 1)
  {
    ISR_func_ptr_1 = ISR_ptr;
  }
  else
  {
    Serial.println("ERROR : Please use 0 or 1 interrupt number !!");
    return;
  }
  
  //pinMode(2, INPUT);
  DDRD &= ~(0x01 << int_pin_num);   //PD2 
  
  //attachInterrupt(0, remoconISR, FALLING);
  EICRA = mode << int_pin_num * 2;
  EIMSK = 0x01 << int_pin_num;
}

SIGNAL(INT0_vect)
{
  ISR_func_ptr_0();
}

SIGNAL(INT1_vect)
{
  ISR_func_ptr_1();
}
