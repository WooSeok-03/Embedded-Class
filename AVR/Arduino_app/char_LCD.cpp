#include "char_LCD.h"

//#define RS  3
//#define RW  4 
//#define E   5
//#define DB0 6
//#define DB1 7
//#define DB2 8
//#define DB3 9
//#define DB4 10
//#define DB5 11
//#define DB6 12
//#define DB7 13

char RS;
char RW;
char E;
char DB[8];

//8bit
//----------------------------------------------------------------
void char_lcd_init_8bit(char *pin)
{
	for (int i = 0; i < 11; i++) pinMode(pin[i], OUTPUT);
	RS = pin[0];
	RW = pin[1];
	E = pin[2];
	for (int i = 0; i < 8; i++) DB[i] = pin[i + 3];

	char_lcd_inst_8bit(0x30);
	char_lcd_inst_8bit(0x30);
	char_lcd_inst_8bit(0x30);
	char_lcd_inst_8bit(0x38);
	char_lcd_inst_8bit(0x06);
	char_lcd_inst_8bit(0x0C);
	char_lcd_inst_8bit(0x80);
	char_lcd_inst_8bit(0x01);
	delay(10);
}

void char_lcd_inst_8bit(char inst)
{
	digitalWrite(RS, LOW);
	
	for (int i = 0; i < 8; i++)
	{
		if (inst & (0x01 << i))
		{
			digitalWrite(DB[i], HIGH);
		}
		else
		{
			digitalWrite(DB[i], LOW);
		}
	}

	digitalWrite(E, HIGH);
	digitalWrite(E, LOW);

	digitalWrite(RS, HIGH);

	delayMicroseconds(50);
}


void char_lcd_data_8bit(char data)
{

	for (int i = 0; i < 8; i++)
	{
		if (data & (0x01 << i))
		{
			digitalWrite(DB[i], HIGH);
		}
		else
		{
			digitalWrite(DB[i], LOW);
		}
	}

	digitalWrite(E, HIGH);
	digitalWrite(E, LOW);

  delayMicroseconds(50);
}

//----------------------------------------------------------------

//4bit
//----------------------------------------------------------------
void char_lcd_init_4bit(char* pin)
{
	for (int i = 0; i < 7; i++) pinMode(pin[i], OUTPUT);
	RS = pin[0];
	RW = pin[1];
	E = pin[2];
	for (int i = 0; i < 4; i++) DB[i] = pin[3 + i];

	char_lcd_inst_8bit(0x30);
	char_lcd_inst_8bit(0x30);
	char_lcd_inst_8bit(0x30);
	char_lcd_inst_8bit(0x28);

	char_lcd_inst_4bit(0x06);
	char_lcd_inst_4bit(0x0C);
	char_lcd_inst_4bit(0x80);
	char_lcd_inst_4bit(0x01);
	
	delay(10);
}

void char_lcd_inst_4bit(char inst)
{
	char_lcd_inst_4bit_HIGH(inst);
	char_lcd_inst_4bit_LOW(inst);
}

void char_lcd_inst_4bit_HIGH(char inst_high)
{
	digitalWrite(RS, LOW);

	for (int i = 0; i < 4; i++)
	{
		if (inst_high & (0x10 << i))
		{
			digitalWrite(DB[i], HIGH);
		}
		else
		{
			digitalWrite(DB[i], LOW);
		}
	}

	digitalWrite(E, HIGH);
	digitalWrite(E, LOW);

	digitalWrite(RS, HIGH);

	delayMicroseconds(50);
}

void char_lcd_inst_4bit_LOW(char inst_low)
{
	digitalWrite(RS, LOW);

	for (int i = 0; i < 4; i++)
	{
		if (inst_low & (0x01 << i))
		{
			digitalWrite(DB[i], HIGH);
		}
		else
		{
			digitalWrite(DB[i], LOW);
		}
	}

	digitalWrite(E, HIGH);
	digitalWrite(E, LOW);

	digitalWrite(RS, HIGH);

	delayMicroseconds(50);
}

void char_lcd_data_4bit(char data_high)
{
  char_lcd_data_4bit_HIGH(data);
  char_lcd_data_4bit_LOW(data);
}

void char_lcd_data_4bit_HIGH(char data_high)
{

	for (int i = 0; i < 4; i++)
	{
		if (data_high & (0x10 << i))
		{
			digitalWrite(DB[i], HIGH);
		}
		else
		{
			digitalWrite(DB[i], LOW);
		}
	}

	digitalWrite(E, HIGH);
	digitalWrite(E, LOW);

	delayMicroseconds(50);
}

void char_lcd_data_4bit_LOW(char data_low)
{
  for(int i=0;i<4;i++) {
    if(data_low & (0x01 << i)) {
      digitalWrite(DB[i], HIGH);
    }
    else {
      digitalWrite(DB[i], LOW);
    }
  }
  
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  delayMicroseconds(50);
}
