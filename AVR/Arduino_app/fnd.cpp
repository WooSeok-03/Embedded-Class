#include "fnd.h"
#include "gpio.h"

char fnd_number[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8
  {1, 1, 1, 0, 0, 1, 1, 0}, // 9
};

char fnd_pin_num[8];
char common_pin[4];
char c_anode_cathode = 0;
char fndCount = 0;
char current_digit = 0;
char digit_num[4];

void fnd_init_1(char *fnd_pin, char common)
{
  c_anode_cathode= common;
  for(int i = 0; i < 8; i++)
  {
    pin_mode(fnd_pin[i], OUTPUT);
    fnd_pin_num[i] = fnd_pin[i];
  }
}

void fnd_num_1(char num)
{
  for(int i = 0; i < 8; i++)
  {
    if(c_anode_cathode == C_CATHODE)
      digital_write(fnd_pin_num[i], fnd_number[num][i]);
    else
      digital_write(fnd_pin_num[i], ~fnd_number[num][i]);
  }
}

//---------------------------------------------------------------------

void fnd_init_2(char fnd_count, char *fnd_pin, char common)
{
  c_anode_cathode= common;
  fndCount = fnd_count;
  for(int i = 0; i < 8; i++)
  {
    pin_mode(fnd_pin[i], OUTPUT);
    fnd_pin_num[i] = fnd_pin[i];
  }

  for(int i = 0; i < fnd_count; i++)
  {
    pin_mode(fnd_pin[i+8], OUTPUT);
    common_pin[i] = fnd_pin[i+8];
  }
}

// 1. all power off
// 2. right number input
// 3. right power on
// 4. delay

void fnd_num_2(char num)
{
  //All power off
  for(int i = 0; i < fndCount; i++)
  {
    digital_write(common_pin[i], HIGH);
  }
  
  //Right number input
  char num_1 = num % 10;
  for(int i = 0; i < 8; i++)
  {
    if(c_anode_cathode == C_CATHODE)
      digital_write(fnd_pin_num[i], fnd_number[num_1][i]);
    else
      digital_write(fnd_pin_num[i], ~fnd_number[num_1][i]);
  }

  //Right power on
  digital_write(common_pin[0], LOW);
  //delay 10ms
  delay(10);

  //----------------------------------------------------------------------
  
  //All power off
  for(int i = 0; i < fndCount; i++)
  {
    digital_write(common_pin[i], HIGH);
  }
  
  //Left number input
  char num_10 = (num % 100) / 10;
  for(int i = 0; i < 8; i++)
  {
    if(c_anode_cathode == C_CATHODE)
      digital_write(fnd_pin_num[i], fnd_number[num_10][i]);
    else
      digital_write(fnd_pin_num[i], ~fnd_number[num_10][i]);
  }

  //Left power on
  digital_write(common_pin[1], LOW);
  //delay 10ms
  delay(10);
}

//---------------------------------------------------------------------------

void fnd_init(char fnd_count, char *fnd_pin, char common)
{
  c_anode_cathode= common;
  fndCount = fnd_count;
  for(int i = 0; i < 8; i++)
  {
    pin_mode(fnd_pin[i], OUTPUT);
    fnd_pin_num[i] = fnd_pin[i];
  }

  for(int i = 0; i < fnd_count; i++)
  {
    pin_mode(fnd_pin[i+8], OUTPUT);
    common_pin[i] = fnd_pin[i+8];
  }
}

void fnd_num_delay(char num)
{
  //All power off
  for(int i = 0; i < fndCount; i++)
  {
    digital_write(common_pin[i], HIGH);
  }
  
  //Number input
  if(fndCount >= 1) digit_num[0] = num % 10;            // 1의 자리
  if(fndCount >= 2) digit_num[1] = (num % 100) / 10;    // 10의 자리
  if(fndCount >= 3) digit_num[2] = (num % 1000) / 100;  // 100의 자리
  if(fndCount >= 4) digit_num[3] = num / 1000;          // 1000의 자리
  
  for(int i = 0; i < 8; i++)
  {
    if(c_anode_cathode == C_CATHODE)
      digital_write(fnd_pin_num[i], fnd_number[current_digit][i]);
    else
      digital_write(fnd_pin_num[i], ~fnd_number[current_digit][i]);
  }

  //Power on
  digital_write(common_pin[current_digit], LOW);
  //delay 10ms
  current_digit++;
  if(current_digit == 4) current_digit = 0;
  delay(10 / fndCount);
}

//============================================================================

unsigned long previous_millis = 0;

void fnd_num_millis(unsigned long current_millis, char num)
{
  if (current_millis - previous_millis > 10 / fndCount)
  {
    previous_millis = current_millis;
  
    //All power off
    for(int i = 0; i < fndCount; i++)
    {
      digital_write(common_pin[i], HIGH);
    }
  
    //Right number input
    if(fndCount >= 1) digit_num[0] = num % 10;            // 1의 자리
    if(fndCount >= 2) digit_num[1] = (num % 100) / 10;    // 10의 자리
    if(fndCount >= 3) digit_num[2] = (num % 1000) / 100;  // 100의 자리
    if(fndCount >= 4) digit_num[3] = num / 1000;          // 1000의 자리
  
    for(int i = 0; i < 8; i++)
    {
      if(c_anode_cathode == C_CATHODE)
        digital_write(fnd_pin_num[i], fnd_number[current_digit][i]);
      else
        digital_write(fnd_pin_num[i], ~fnd_number[current_digit][i]);
    }

    //Right power on
    digital_write(common_pin[current_digit], LOW);
    //delay 10ms
    current_digit++;
    if(current_digit == 4) current_digit = 0;
  }
}
