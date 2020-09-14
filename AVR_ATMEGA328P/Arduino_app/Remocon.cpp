#include "Remocon.h"

char rem_int_count = 0;
unsigned long int_time[40];
int diff_time[33];
char rem_bit[32];
char remocon_num = 0x00;
char remocon_finish_flag = 0;

char rem_8bit_data[21][8] = {
  {0, 1, 1, 0, 1, 0, 0, 0}, // 0
  {0, 0, 1, 1, 0, 0, 0, 0}, // 1
  {0, 0, 0, 1, 1, 0, 0, 0}, // 2
  {0, 1, 1, 1, 1, 0, 1, 0}, // 3
  {0, 0, 0, 1, 0, 0, 0, 0}, // 4
  {0, 0, 1, 1, 1, 0, 0, 0}, // 5
  {0, 1, 0, 1, 1, 0, 1, 0}, // 6
  {0, 1, 0, 0, 0, 0, 1, 0}, // 7
  {0, 1, 0, 0, 1, 0, 1, 0}, // 8
  {0, 1, 0, 1, 0, 0, 1, 0}, // 9
  {1, 0, 0, 1, 1, 0, 0, 0}, // 100+
  {1, 0, 1, 1, 0, 0, 0, 0}, // 200+
  {1, 1, 1, 0, 0, 0, 0, 0}, // -
  {1, 1, 0, 1, 0, 1, 0, 0}, // +
  {1, 0, 0, 1, 0, 0, 0, 0}, // EQ
  {0, 0, 1, 0, 0, 0, 1, 0}, // PREV
  {1, 1, 0, 0, 0, 1, 0, 1}, // NEXT
  {1, 1, 0, 0, 0, 0, 1, 0}, // PLAY/PAUSE
  {1, 1, 1, 1, 1, 1, 1, 1}, // CH-
  {1, 1, 1, 1, 1, 1, 1, 0}, // CH
  {1, 1, 1, 0, 0, 0, 1, 0} // CH+
};

void remocon_init(char int_pin)
{
  exti_init(int_pin - 2, EXTI_FALLING, remoconISR);
  
  //pinMode(2, INPUT);
  //DDRD &= ~(0x01 << int_pin);   //PD2 
  
  //attachInterrupt(0, remoconISR, FALLING);
  //EICRA |= 0x02 << (int_pin - 2) * 2;
  //EIMSK |= 0x01 << (int_pin - 2); //0번
}

void remocon_proc()
{
  
}

void int_callback_flag_clear()
{
  remocon_finish_flag = 0;
}

char remocon_callback(char *rem_number)
{
  *rem_number = remocon_num;
  return remocon_finish_flag;
}


//SIGNAL(INT0_vect)
void remoconISR()
{
  int_time[rem_int_count] = micros();
  /*
  if(rem_int_count > 0)
  {
    if( (int_time[rem_int_count] - int_time[rem_int_count - 1]) > 12500 &&
        (int_time[rem_int_count] - int_time[rem_int_count - 1]) < 14500 )
    {
      rem_int_count = 1;
      Serial.println("Lead Code");
    }
  }
  */

  if(rem_int_count > 0)
  {
    if( (int_time[rem_int_count] - int_time[rem_int_count - 1]) > 13000 &&
        (int_time[rem_int_count] - int_time[rem_int_count - 1]) < 14000 )
    {
      rem_int_count = 1;
      //Serial.println("Lead Code");
    }
  }

  if(rem_int_count > 0)
  {
    if( (int_time[rem_int_count] - int_time[rem_int_count - 1]) > 11000 &&
        (int_time[rem_int_count] - int_time[rem_int_count - 1]) < 12000 )
    {
      //Serial.println("R");
      Serial.println(remocon_num);
    }
    diff_time[rem_int_count - 1] = int_time[rem_int_count] - int_time[rem_int_count - 1];   //diff_time에 33개 들어감.
  }

  
  rem_int_count++;
  if(rem_int_count == 34)
  {
    rem_int_count = 0;

    for(int i = 0; i < 32; i++) 
    {
      if(diff_time[i + 1]> 1000 && diff_time[i + 1]< 1500)
      {
        rem_bit[i] = 0;
      }
      else if(diff_time[i + 1]> 2000 && diff_time[i + 1]< 2500)
      {
        rem_bit[i] = 1;
      }
      
    }

    remocon_num = 0x00;
    for(int j = 0; j < 2; j++)
    {
      int count = 0;
      for(int i = 0; i < 8; i++) 
      {
        if(rem_bit[i + 16] == rem_8bit_data[j][i]) count++;
      }
      if(count == 8)
      {
        remocon_num = j + 0x30;
        remocon_finish_flag = 1;
        //Serial.print(remocon_num);
        break;
      }
    }

    /*
    for(int i = 0; i < 32; i++) 
    {
      Serial.print(rem_bit[i], HEX);
      //Serial.println(diff_time[i + 1]);
    }
    */
    
    //Serial.println("int count == 34");
  }
}
