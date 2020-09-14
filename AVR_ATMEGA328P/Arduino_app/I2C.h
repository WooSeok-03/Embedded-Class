#ifndef I2C_H
#define I2C_H

#include "Arduino.h"

void I2C_init();
void I2C_start();
void I2C_stop();
void data_8bit_set(char data);
void I2C_ack();
void I2C_byte_write(char addr, char data);

#endif
