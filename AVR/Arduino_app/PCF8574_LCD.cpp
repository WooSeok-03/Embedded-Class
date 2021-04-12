#include "PCF8574_LCD.h"

#define SCL 19
#define SDA 18

#define E 10
#define RS 11

char PCF8574_LCD = 0;

int DB8574[10];

void PCF8574_LCD_init()
{
	I2C_init(SCL, SDA);

	PCF8574_LCD |= 0x01;
}

void I2C_8bit_data_write(int a, int b)
{
  
}

void PCF8574_LCD_backlight_on_off(char on_off)
{
	if (on_off == 1)
	{
		I2C_8bit_data_write(0x27, 0x80);
	}
	else
	{
		I2C_8bit_data_write(0x27, 0x00);
	}
}

unsigned long c_millis_8574 = 0;
unsigned long p_millis_8574 = 0;
unsigned long c_micros = 0;
unsigned long p_micros_8574 = 0;
unsigned char PCF8574_LCD_pwm_count = 0;
unsigned char PCF8574_LCD_pwm_duty = 0;

void PVF8574_LCD_backlight_PWM(char current_millis, char current_micros, char PCF8574_LCD_pwm_duty)
{
	c_micros = current_micros;
	c_millis_8574 = current_millis;

	if (c_micros - p_micros_8574 > 100)
	{
		p_micros_8574 = c_micros;
		
		if (PCF8574_LCD_pwm_count == 100)
		{
			PCF8574_LCD_pwm_count = 0;
			PCF8574_LCD_backlight_on_off(1);
		}
		else if (PCF8574_LCD_pwm_count == PCF8574_LCD_pwm_duty)
		{
			PCF8574_LCD_backlight_on_off(0);
		}

		PCF8574_LCD_pwm_count++;


	}

	if (c_millis_8574 - p_millis_8574 > 10)
	{
		p_millis_8574 = c_millis_8574;
	}
}

//----------------------------------------------------------------------------

void PCF8574_LCD_data_4bit()
{
	//PCF8574_LCD_4bit_HIGH();
	//PCF8574_LCD_4bit_LOW();
}

void PCF8574_LCD_4bit_HIGH(char inst_high)
{
	PCF8574_LCD |= ((inst_high & 0xF0) >> 4);
	I2C_8bit_data_write(0x27, PCF8574_LCD);

	//E HIGH
	PCF8574_LCD |= 0x04;
	I2C_8bit_data_write(0x27, PCF8574_LCD);

	//E LOW
	PCF8574_LCD &= ~0x04;
	I2C_8bit_data_write(0x27, PCF8574_LCD);
}

void PCF8574_LCD_4bit_LOW()
{

}

//----------------------------------------------------------------------------

void PCF8574_LCD_inst_8bit(char inst)
{
	//RS LOW
	PCF8574_LCD &= ~0x01;
	I2C_8bit_data_write(0x27, PCF8574_LCD);

	for (int i = 0; i < 8; i++)
	{
		if (inst & (0x01 << 1))
		{
			digitalWrite(DB8574[i], HIGH);
		}
		else
		{
			digitalWrite(DB8574[i], LOW);
		}
	}

	digitalWrite(E, HIGH);
	digitalWrite(E, LOW);

	digitalWrite(RS, HIGH);

	delayMicroseconds(50);
}
