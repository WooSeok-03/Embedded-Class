#ifndef PCF8574_LCD_H
#define PCF8574_LCD_H

#include "Arduino.h"
#include "I2C.h"

void PCF8574_LCD_init();
void PCF8574_LCD_backlight_on_off(char on_off);
void PVF8574_LCD_backlight_PWM(char current_millis, char current_micros, char PCF8574_LCD_pwm_duty);

#endif // !PCF8574_LCD_H
