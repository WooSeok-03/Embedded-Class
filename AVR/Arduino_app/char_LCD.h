#ifndef CHAR_LCD_H
#define CHAR_LCD_H

#include "Arduino.h"

// 8bit
void char_lcd_init_8bit(char *pin);
void char_lcd_inst_8bit(char inst);
void char_lcd_data_8bit(char data);

// 4bit
void char_lcd_init_4bit(char* pin); 
void char_lcd_data_4bit(char inst);

void char_lcd_inst_4bit_HIGH(char inst_high);
void char_lcd_inst_4bit_LOW(char inst_low);

void char_lcd_data_4bit_HIGH(char data_high);
void char_lcd_data_4bit_LOW(char data_low);

#endif
