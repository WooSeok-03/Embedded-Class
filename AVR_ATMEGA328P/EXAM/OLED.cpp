#include "OLED.h"

char pre_x = 0;
char pre_y = 0;

short mouse_pointer[17][11] = {
  {1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2},
  {1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2},
  {1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2},
  {1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2},
  {1, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2},
  {1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2},
  {1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
  {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {1, 0, 0, 1, 0, 0, 1, 2, 2, 2, 2},
  {1, 0, 1, 1, 0, 0, 1, 2, 2, 2, 2},
  {1, 1, 2, 2, 1, 0, 0, 1, 2, 2, 2},
  {1, 2, 2, 2, 1, 0, 0, 1, 2, 2, 2},
  {2, 2, 2, 2, 2, 1, 0, 0, 1, 2, 2},
  {2, 2, 2, 2, 2, 1, 0, 0, 1, 2, 2},
  {2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2},
};

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

  main_menu();
}

void spi_init()
{
  SPCR = 0x50;
  SPSR = 0x01;
}

void spi_write(char data)
{
  SPDR = data;
  while (!(SPSR & 0x80));
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
  char first_byte = (color >> 8) & 0xff;
  char second_byte = color & 0xff;
  Write_Command(0x15);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(0x00);
  Write_Data(0x7f);

  Write_Command(0x5c);

  for (int j = 0; j < 128; j++)
  {
    for (int i = 0; i < 128; i++)
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

void draw_bitmap_top(unsigned char bitmap[])
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

  for (int j = 0; j < 64; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      Write_Data(pgm_read_byte(&bitmap[0x46 + 1 + i * 2 + j * 128 * 2]));
      Write_Data(pgm_read_byte(&bitmap[0x46 + i * 2 + j * 128 * 2]));
    }
  }
}


void draw_bitmap_bottom(unsigned char bitmap[])
{
  Write_Command(0x15);
  Write_Data(0x00);
  //Write_Data(127);
  Write_Data(0x7f);

  Write_Command(0x75);
  Write_Data(64);
  Write_Data(127);

  Write_Command(0x5c);

  for (int j = 0; j < 64; j++)
  {
    for (int i = 0; i < 128; i++)
    {
      Write_Data(pgm_read_byte(&bitmap[0x46 + 1 + i * 2 + j * 128 * 2]));
      Write_Data(pgm_read_byte(&bitmap[0x46 + i * 2 + j * 128 * 2]));
    }
  }
}

void font_write(char x, char y, unsigned short color, char font)
{
  for (int j = 0; j < 16; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      if (ascii_8x16[font - 0x20][j] & (0x80 >> i))
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

  for (int i = 0; i < str_len; i++)
  {
    font_write(x + (i * 10), y, color, *(str + i));
  }
}

void make_rect(char x, char y)
{
  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < 10; i++)
    {
      put_pixel(x + i, y + j, RED);
    }
  }
}

void delete_rect(char x, char y)
{
  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < 10; i++)
    {
      put_pixel(x + i, y + j, WHITE);
    }
  }
}

void clear_string()
{
  for (int j = 0; j < 30; j++)
  {
    for (int i = 0; i < 50; i++)
    {
      put_pixel(30 + i, 50 + j, WHITE);
    }
  }
}

void draw_mouse_pointer(char x, char y)
{
  for (int j = 0; j < 17; j++)
  {
    for (int i = 0; i < 11; i++)
    {
      if (mouse_pointer[j][i] == 1) put_pixel(x + i, y + j, BLACK);
      else if (mouse_pointer[j][i] == 0) put_pixel(x + i, y + j, WHITE);
    }
  }
}

void mouse_pointer_move(char x, char y, char c_choice)
{
  if (pre_x != x || pre_y != y)
  {
    draw_save_background(pre_x, pre_y);
    draw_mouse_pointer(x, y);
  }
  pre_x = x;
  pre_y = y;
}

void save_bitmap(char x, char y, unsigned char first_byte, unsigned char second_byte)
{
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

void draw_save_background(char x, char y)
{
  for (int j = 0; j < 17; j++)
  {
    for (int i = 0; i < 11; i++)
    {
      if (y + j < 64) save_bitmap(x + i, y + j, pgm_read_byte(&exam_top[0x46 + 1 + (i + x) * 2 + (j + y) * 128 * 2]), pgm_read_byte(&exam_top[0x46 + (i + x) * 2 + (j + y) * 128 * 2]));
      else save_bitmap(x + i, y + j, pgm_read_byte(&exam_bottom[0x46 + 1 + (i + x) * 2 + (j + y - 64) * 128 * 2]), pgm_read_byte(&exam_bottom[0x46 + (i + x) * 2 + (j + y - 64) * 128 * 2]));
    }
  }
}

int selection_area(char x, char y)
{
  //Servo Area
  if ((x > 27 && x < 65) && (y >= 0 && y < 47)) return 0;

  //PWM Area
  else if ((x > 65 && x < 100) && (y >= 0 && y < 47)) return 1;

  //Ultrasonic Area
  else if ((x > 99 && x < 128) && (y > 47 && y < 80)) return 2;

  //input Area
  else if ((x > 65 && x < 100) && (y > 79 && y < 128)) return 3;

  //I2C Area
  else if ((x > 27 && x < 65) && (y > 79 && y < 128)) return 4;

  //Remocon Area
  else if ((x >= 0 && x < 27) && (y > 47 && y < 80)) return 5;
}

void draw_selection_click(int select)
{
  if (select == 0) //Servo
  {
    for (int j = 0; j < 3; j++)
    {
      for (int i = 0 ; i < 36; i++)
      {
        put_pixel(28 + i, 42 + j, BLUE);
      }
    }
  }
  else if (select == 1) //PWM
  {
    for (int j = 0; j < 3; j++)
    {
      for (int i = 0 ; i < 33; i++)
      {
        put_pixel(67 + i, 42 + j, BLUE);
      }
    }
  }
  else if (select == 2) //UltraSonic
    for (int i = 0 ; i < 31; i++) put_pixel(101, 49 + i, BLUE);
    
else if (select == 3) //input
{
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0 ; i < 33; i++)
    {
      put_pixel(67 + i, 82 + j, BLUE);
    }
  }
}
else if (select == 4) //I2C
{
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0 ; i < 36; i++)
    {
      put_pixel(28 + i, 82 + j, BLUE);
    }
  }
}
else if (select == 5) //Remocon
{
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0 ; i < 31; i++)
    {
      put_pixel(25 + j, 49 + i, BLUE);
    }
  }
}
}

void delete_selection_click()
{
  //Servo
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0 ; i < 36; i++)
    {
      put_pixel(28 + i, 42 + j, WHITE);
    }
  }

  //PWM
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0 ; i < 33; i++)
    {
      put_pixel(67 + i, 42 + j, WHITE);
    }
  }

  //UltraSonic
  for (int i = 0 ; i < 31; i++) put_pixel(101, 49 + i, WHITE);

  //input
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0 ; i < 33; i++)
    {
      put_pixel(67 + i, 82 + j, WHITE);
    }
  }

  //I2C
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0 ; i < 36; i++)
    {
      put_pixel(28 + i, 82 + j, WHITE);
    }
  }

  //Remocon
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0 ; i < 31; i++)
    {
      put_pixel(25 + j, 49 + i, WHITE);
    }
  }
}

void main_menu()
{
  draw_bitmap_top(exam_top);
  draw_bitmap_bottom(exam_bottom);

  draw_mouse_pointer(0, 0);

  make_rect(40,5);
}
