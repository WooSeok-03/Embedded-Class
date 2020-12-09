#include "keypad.h"

unsigned long key_millis = 0;
int keyInputCount = 0;

void keypadInit() {
   for (int i = 0; i < 4; i++) {
    pinMode(COL + (i*2), OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(ROW - (i*2), INPUT);
  }
}

void keyInput(unsigned long c_millis) {
  if (c_millis - key_millis > 10) {
    key_millis = c_millis;

    if(keyInputCount == 9 || keyInputCount == 10) keyInputCount = 0;
 
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
        if (i == j) {
          digitalWrite(COL + (i*2), HIGH);
        } else {
          digitalWrite(COL + (i*2), LOW);
        }
      }

      for (int  i = 0; i < 4; i++) {
        if (digitalRead(ROW - (i*2))) {
          keyInputCount = i * 4 + j + 1;
        }
      }
    }
  }
}

int getInputNumber() {
  return keyInputCount;
}
