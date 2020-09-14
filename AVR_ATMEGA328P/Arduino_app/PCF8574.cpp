#include "I2C.h"

char char_ldc_8bit_data = 0;

char char_lcd_init()
{
  //RS LOW
  char_lcd_8bit_data = 0;
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //RW LOW
  char_lcd_8bit_data &= ~(0x01 << 1);
  I2C_byte_write(0x27, char_lcd_8bit_data);

  //data 8bit
  char_lcd_8bit_data |= 0x30;
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //E HIGH
  char_lcd_8bit_data |= (0x01 << 2);
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //E LOW
  char_lcd_8bit_data &= ~(0x01 << 2);
  I2C_byte_write(0x27, char_lcd_8bit_data);
}


char char_lcd_8bit_set_inst()
{
  //RS LOW
  char_lcd_8bit_data = 0;
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //RW LOW
  char_lcd_8bit_data &= ~(0x01 << 1);
  I2C_byte_write(0x27, char_lcd_8bit_data);

  //data 8bit
  char_lcd_8bit_data |= 0x30;
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //E HIGH
  char_lcd_8bit_data |= (0x01 << 2);
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //E LOW
  char_lcd_8bit_data &= ~(0x01 << 2);
  I2C_byte_write(0x27, char_lcd_8bit_data);
}


char char_lcd_4bit_set_high_inst()
{
  //RS LOW
  char_lcd_8bit_data = 0;
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //RW LOW
  char_lcd_8bit_data &= ~(0x01 << 1);
  I2C_byte_write(0x27, char_lcd_8bit_data);

  //data 8bit
  char_lcd_8bit_data |= 0x30;
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //E HIGH
  char_lcd_8bit_data |= (0x01 << 2);
  I2C_byte_write(0x27, char_lcd_8bit_data);
  
  //E LOW
  char_lcd_8bit_data &= ~(0x01 << 2);
  I2C_byte_write(0x27, char_lcd_8bit_data);
}
