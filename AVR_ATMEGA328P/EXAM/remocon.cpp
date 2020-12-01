#include "remocon.h"

char rem_int_count = 0;
unsigned long int_time[40] = {0,};
int remocon_diff_time[33] = { 0, };
char remocon_bit[32];
char remocon_num = 0x00;
char rem_8bit_data[10][8] = {
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
};

char getRemoconNum() {
  return remocon_num;
}

void remoconInit() {
  DDRE &= ~0x20;
  
  EICRB |= 0x08;
  EIMSK |= 0x20;
}

SIGNAL(INT5_vect) {
  int_time[rem_int_count] = micros();

  if (rem_int_count > 0) {
    if ((int_time[rem_int_count] - int_time[rem_int_count - 1]) > 13000 &&
        (int_time[rem_int_count] - int_time[rem_int_count - 1]) < 14000) {
      rem_int_count = 1;
    }
    else if ((int_time[rem_int_count] - int_time[rem_int_count - 1]) > 11000 &&
             (int_time[rem_int_count] - int_time[rem_int_count - 1]) < 12000) {
    }

    remocon_diff_time[rem_int_count - 1] = (int_time[rem_int_count] - int_time[rem_int_count - 1]);
  }

  rem_int_count++;

  if (rem_int_count == 34) {
    rem_int_count = 0;
    for (int i = 0; i < 32; i++) {
      if (remocon_diff_time[i + 1] > 1000 &&
          remocon_diff_time[i + 1] < 1500) {
        remocon_bit[i] = 0;
      }
      else if (remocon_diff_time[i + 1] > 2000 &&
               remocon_diff_time[i + 1] < 2500) {
        remocon_bit[i] = 1;
      }
    }
    remocon_num = 0x00;

    for (int j = 0; j < 10; j++)
    {
      int count = 0;
      for (int i = 0; i < 8; i++) {
        if (remocon_bit[16 + i] == rem_8bit_data[j][i]) {
          count++;
        }
      }
      if (count == 8) {
        remocon_num = j + 0x30;
        //Serial.println(remocon_num);
        break;
      }
    }
  }
}
