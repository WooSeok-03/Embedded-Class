#ifndef I2C_LCD_H
#define I2C_LCD_H

#include "Arduino.h"

#define SDA 20
#define SCL 21
#define PCF_8574_ADDR 0x27

void i2c_init();
void backlightONOFF(unsigned long c_millis);
void i2c_start();
void i2c_stop();
void i2c_ack();
void i2c_8bit(char data);
void pcf8574_data_set(char data);
void light_off();

#endif
