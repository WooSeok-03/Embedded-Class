#ifndef OLED_H
#define OLED_H

#include "Arduino.h"

#include "font.h"
#include "exam_top.h"
#include "exam_bottom.h"

#define OLED_CS   9
#define OLED_RST  8
#define OLED_DC   10

#define OLED_SCK  52
#define OLED_DATA 51

#define RED    0xf800
#define GREEN  0x07e0
#define BLUE   0x001f
#define WHITE  0xffff
#define BLACK  0x0000

void oled_set();
void spi_init();
void spi_write(char data);
void Write_Command(char command);
void Write_Data(char data);
void clear_screen(unsigned short color);
void draw_bitmap_top();
void draw_bitmap_bottom();
void font_write(char x, char y, unsigned short color, char font);
void string_write(char x, char y, unsigned short color, char *str);
void draw_line_hori(int x_start, int x_end, int y, unsigned short color);
void draw_line_vert(int y_start, int y_end, int x, unsigned short color);
void delete_rect(char x, char y);
void make_rect(char x, char y);
void clear_string();


#endif
