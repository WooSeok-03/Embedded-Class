#include "OLED.h"

void oled_init()
{
  digitalWrite(OLED_CS, LOW);
  digitalWrite(OLED_RST, LOW);
  delay(100);
  digitalWrite(OLED_RST, HIGH);
  delay(100);

  Write_Command(0xfd);  // command lock
  Write_Data(0x12);
  Write_Command(0xfd);  // command lock
  Write_Data(0xB1);

  Write_Command(0xae);  // display off
  
  Write_Command(0xB3);
  Write_Data(0xF1);

  Write_Command(0xa0);  //set re-map & data format
  Write_Data(0x74); //Horizontal address increment
  
  Write_Command(0xCA);  
  Write_Data(0x7F);

  Write_Command(0xa2);  //set display offset
  Write_Data(0x00);

  Write_Command(0xB5);  
  Write_Data(0x00);

  Write_Command(0xAB);
  Write_Data(0x01);

  Write_Command(0xB1);
  Write_Data(0x32);

  Write_Command(0xBE);
  Write_Data(0x05);

  Write_Command(0xA6);

  Write_Command(0xC1);
  Write_Data(0xC8);
  Write_Data(0x80);
  Write_Data(0xC8);  

  Write_Command(0xC7);
  Write_Data(0x0F);

  Write_Command(0xB4);
  Write_Data(0xA0);
  Write_Data(0xB5);
  Write_Data(0x55);  
  
  Write_Command(0xB6);
  Write_Data(0x01);

  Write_Command(0xAF);  
}

void oled_set()
{
  pinMode(53, OUTPUT); // Mega
  
  pinMode(OLED_RST, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_SCK, OUTPUT);
  pinMode(OLED_DATA, OUTPUT);

  digitalWrite(OLED_SCK, LOW);

  spi_init();
  oled_init();

  draw_bitmap_top();
  draw_bitmap_bottom();

  make_rect(40,5);
}

void spi_init()
{
  SPCR = 0x50;
  SPSR = 0x01;
}

void spi_write(char data)
{
  SPDR = data;
  while(!(SPSR & 0x80)); 
}

void Write_Command(char command)
{
  digitalWrite(OLED_CS, LOW);   // CS LOW
  digitalWrite(OLED_DC, LOW);   // DC LOW

  spi_write(command);
  
  digitalWrite(OLED_CS, HIGH);  // CS HIGH
  digitalWrite(OLED_DC, HIGH);  // DC HIGH
}

void Write_Data(char data)
{
  digitalWrite(OLED_CS, LOW);   // CS LOW
  //shift_out(data);
  spi_write(data);
  digitalWrite(OLED_CS, HIGH);  // CS HIGH
}



void clear_screen(unsigned short color)
{
  char first_byte = (color & 0xff) >> 8;
  char second_byte = color & 0xff;
  Write_Command(0x15);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x5c);

  for(int j = 0; j < 128; j++)
  {
    for(int i = 0; i < 128; i++)
    {
      Write_Data(first_byte);
      Write_Data(second_byte);
    }
  }
}

void put_pixel(char x, char y, unsigned short color)
{
  char first_byte = (color & 0xff00) >> 8;
  char second_byte = color & 0xff;
  
  //Column
  Write_Command(0x15);
  Write_Data(x); 
  Write_Data(x);

  //Row
  Write_Command(0x75);
  Write_Data(y);
  Write_Data(y);

  Write_Command(0x5c);

  Write_Data(first_byte);
  Write_Data(second_byte);
}

void draw_bitmap_top()
{
  Write_Command(0x15);
  Write_Data(0x00);
  Write_Data(127); 
  //Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  Write_Data(63);
  //Write_Data(0x7f);

  Write_Command(0x5c);

  for(int j = 0; j < 64; j++)
  {
    for(int i = 0; i < 128; i++)
    {
      Write_Data(pgm_read_byte(&exam_top[0x46 + 1 + i*2 + j*128*2]));
      Write_Data(pgm_read_byte(&exam_top[0x46 + i*2 + j*128*2]));
    }
  }
}

void draw_bitmap_bottom()
{
  Write_Command(0x15);
  Write_Data(0x00);
  //Write_Data(127); 
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(64);
  Write_Data(127);

  Write_Command(0x5c);

  for(int j = 0; j < 64; j++)
  {
    for(int i = 0; i < 128; i++)
    {
      Write_Data(pgm_read_byte(&exam_bottom[0x46 + 1 + i*2 + j*128*2]));
      Write_Data(pgm_read_byte(&exam_bottom[0x46 + i*2 + j*128*2]));
    }
  }
}

void font_write(char x, char y, unsigned short color, char font)
{
  for(int j = 0; j < 16; j++)
  {
    for(int i = 0; i < 8; i++)
    {
      if(ascii_8x16[font - 0x20][j] & (0x80 >> i))
      {
        put_pixel(x + i, y + j, color);
      }
    }
  }
}

void string_write(char x, char y, unsigned short color, char *str)
{
  char font;
  int str_len = strlen(str);
  
  for(int i = 0; i < str_len; i++)
  {
    font_write(x + (i * 10), y, color, *(str + i));
  }
}

void make_rect(char x, char y)
{
  for(int j = 0; j < 10; j++)
  {
    for(int i = 0; i < 10; i++)
    {
      put_pixel(x + i, y + j, RED);
    }
  }
}

void delete_rect(char x, char y)
{
  for(int j = 0; j < 10; j++)
  {
    for(int i = 0; i < 10; i++)
    {
      put_pixel(x + i, y + j, WHITE);
    }
  }
}

void clear_string()
{
  for(int j = 0; j < 30; j++)
  {
    for(int i = 0; i < 50; i++)
    {
      put_pixel(30 + i, 50 + j, WHITE);
    }
  }  
}
