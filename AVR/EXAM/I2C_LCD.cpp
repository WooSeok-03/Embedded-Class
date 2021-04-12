#include "I2C_lcd.h"

unsigned long lcd_p_millis = 0;

void backlightONOFF(unsigned long c_millis) {
  if(c_millis - lcd_p_millis > 2000)
  {
    lcd_p_millis = c_millis;
    pcf8574_data_set(0x08);
    delay(1000);
    pcf8574_data_set(0x00);
  }
}

void light_off()
{
  pcf8574_data_set(0x00);
}

void i2c_init() {
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);

  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}

void i2c_start() {
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
}

void i2c_stop() {
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}

void i2c_ack() {
  pinMode(SDA, INPUT);
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
  //Serial.println("SDA : " + String(digitalRead(SDA)));
  pinMode(SDA, OUTPUT);
}

void i2c_8bit(char data) {
  for (int i = 0; i < 8; i++) {
    if (data & 0x80 >> i) {
      digitalWrite(SDA, HIGH);
    } else {
      digitalWrite(SDA, LOW);
    }

    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }
}

//===========================================

void pcf8574_data_set(char data) {
  i2c_start();
  i2c_8bit(PCF_8574_ADDR << 1);
  i2c_ack();
  i2c_8bit(data);
  i2c_ack();
  i2c_stop();
}
