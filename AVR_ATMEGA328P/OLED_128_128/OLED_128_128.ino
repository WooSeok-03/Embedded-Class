#include "tiger_128_128_16bit.h"
#include "tiger_128_96_16bit.h"
#include "num1_16bit.h"
#include "num2_16bit.h"
#include "num3_16bit.h"
#include "font.h"

#define OLED_CS   4
#define OLED_RST  3
#define OLED_DC   5

// Uno
//#define OLED_SCK  13
//#define OLED_DATA 11

//Mega
#define OLED_SCK  52
#define OLED_DATA 51

#define RED    0xf800
#define GREEN  0x07e0
#define BLUE   0x001f
#define WHITE  0xffff
#define BLACK  0x0000
#define YELLOW 0xffe0

int x = 1;
int y = 1;

char block_L[4][4] = { {0,0,0,0},
                       {0,1,0,0},
                       {0,1,1,1},
                       {0,0,0,0}
};

void setup() {
  //pinMode(10, OUTPUT); // Uno
  pinMode(53, OUTPUT); // Mega
  
  pinMode(OLED_RST, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_SCK, OUTPUT);
  pinMode(OLED_DATA, OUTPUT);

  digitalWrite(OLED_SCK, LOW);

  spi_init();

  oled_init();
  clear_screen(WHITE);

  
  //draw_bitmap();

  //for(int j = 0; j < 10; j++)
  //  for(int i = 0; i < 128; i++)
  //    put_pixel(i, j, 0x001f);  // Color : BLUE

  //font_write(100, 100, 0x001f, '2');
  //string_write(10, 100, 0x001f, "Hello");

  //make_rect(10, 10);
  //make_block(10, 10);

  for(int i = 0; i < 21; i++)
  {
    draw_line_hori(0, 60, i * 6, color_value(200, 200, 200));
  }

  for(int i = 0; i < 11; i++)
  {
    draw_line_vert(0, 121, i * 6, color_value(200, 200, 200));
  }
}

void loop() {
  // 숫자 2, 3 반복
  //draw_num_30_30(50, 50, 2);
  //delay(1000);
  //draw_num_30_30(50, 50, 3);
  //delay(1000);

  // 블럭 1개 떨어뜨리기
  //delete_rect(x, y);
  //y+=6;
  //make_rect(x, y);
  //delay(1000);

  // L자 블럭 떨어뜨리기
  //delete_block(x,y);
  //y+=6;
  //make_block(x,y);
  //delay(1000);
}

// SPCR : SPI Control Register
// SPSR : SPI Status Register
// SPDR : SPI Data Register

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

void shift_out(char data)
{
  for(int i = 0; i < 8; i++)
  {
    // MSB First
    if(data & (0x80 >> i))
    {
      digitalWrite(OLED_DATA, HIGH);
    }
    else
    {
      digitalWrite(OLED_DATA, LOW);
    }
    digitalWrite(OLED_SCK, HIGH);
    digitalWrite(OLED_SCK, LOW);
  }
}

void Write_Command(char command)
{
  digitalWrite(OLED_CS, LOW);   // CS LOW
  digitalWrite(OLED_DC, LOW);   // DC LOW

  shift_out(command);
  
  digitalWrite(OLED_CS, HIGH);  // CS HIGH
  digitalWrite(OLED_DC, HIGH);  // DC HIGH
}


void Write_Data(char data)
{
  digitalWrite(OLED_CS, LOW);   // CS LOW
  shift_out(data);
  digitalWrite(OLED_CS, HIGH);  // CS HIGH
}

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
      //Write_Data(0xF8); //RED
      //White
      Write_Data(0xFF);
      Write_Data(0xFF);
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

unsigned short color_value(char r, char g, char b)
{
  char first_byte = 0;
  char second_byte = 0;
  
  first_byte |= (r & 0xf8) << 3;
  first_byte |= (g & 0x70) >> 5;
  second_byte |= ((g & 0x1c) >> 2) << 5;
  second_byte |= (b & 0xf8) >> 3;
  return ((first_byte << 8) + second_byte);
}

void draw_num_30_30(char x, char y, char number)
{
  char column_x =30;
  char row_y = 30;

  Write_Command(0x15);
  Write_Data(x);
  Write_Data(x + column_x - 1);

  Write_Command(0x75);
  Write_Data(y);
  Write_Data(y + row_y - 1);

  Write_Command(0x5c);

  for(int j = 0; j < row_y; j++)
  {
    for(int i = 0; i < column_x; i++)
    {
      if(number == 1)
      {
        Write_Data(pgm_read_byte(&num1_16bit[0X46 + 1 + i*2 + j*column_x*2]));
        Write_Data(pgm_read_byte(&num1_16bit[0X46 + i*2 + j*row_y*2]));
      }
      else if(number == 2)
      {
        Write_Data(pgm_read_byte(&num2_16bit[0X46 + 1 + i*2 + j*column_x*2]));
        Write_Data(pgm_read_byte(&num2_16bit[0X46 + i*2 + j*row_y*2]));
      }
      else if(number == 3)
      {
        Write_Data(pgm_read_byte(&num3_16bit[0X46 + 1 + i*2 + j*column_x*2]));
        Write_Data(pgm_read_byte(&num3_16bit[0X46 + i*2 + j*row_y*2]));
      }
    }
  }
}

void draw_bitmap()
{
  Write_Command(0x15);
  Write_Data(0x00);
  //Write_Data(127); 
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  //Write_Data(96);
  Write_Data(0x7f);

  Write_Command(0x5c);

  //for(int j = 0; j < 96; j++)
  for(int j = 0; j < 128; j++)
  {
    for(int i = 0; i < 128; i++)
    {
      // pgm_byte 에는 포인터만 들어가기 때문에 &를 붙여줌.
      // 128x128
      Write_Data(pgm_read_byte(&tiger_128_128_16bit[ 1 + i*2 + j*128*2]));
      Write_Data(pgm_read_byte(&tiger_128_128_16bit[ i*2 + j*128*2]));

      //128x96
      //Write_Data(pgm_read_byte(&tiger_128_128_16bit[0x46 + 1 + i*2 + j*128*2]));
      //Write_Data(pgm_read_byte(&tiger_128_128_16bit[0x46 + i*2 j*128*2]));
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
  for(int j = 0; j < 5; j++)
  {
    for(int i = 0; i < 5; i++)
    {
      put_pixel(x + i, y + j, RED);
    }
  }
}

void delete_rect(char x, char y)
{
  for(int j = 0; j < 5; j++)
  {
    for(int i = 0; i < 5; i++)
    {
      put_pixel(x + i, y + j, WHITE);
    }
  }
}

void make_block(char x, char y)
{
  for(int j = 0; j < 4; j++)
  {
    for(int i = 0; i < 4; i++)
    {
      if(block_L[j][i] == 1) make_rect(pixel_offset_x + (x + i) * 6,pixel_offset_y + (y + j) * 6);
    }
  }
}

void delete_block(char x, char y)
{
  for(int j = 0; j < 4; j++)
  {
    for(int i = 0; i < 4; i++)
    {
      if(block_L[j][i] == 1) delete_rect(pixel_offset_x + (x + i) * 6,pixel_offset_y + (y + j) * 6);
    }
  }
}

void draw_line_hori(int x_start, int x_end, int y, unsigned short color)
{
  for(int i = x_start; i < x_end - x_start; i++) put_pixel(x_start + i, y, color);
}

void draw_line_vert(int y_start, int y_end, int x, unsigned short color)
{
  for(int i = y_start; i < y_end - y_start; i++) put_pixel(x, y_start + i, color);
}
