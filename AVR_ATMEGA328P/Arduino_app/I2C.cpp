#include "I2C.h"

#define SCL 5
#define SDA 4

void I2C_init()
{
  //DDRC |= 0x10 | 0x20;  //PC4 : SDA, PC5 : SCL
  DDRC |= 0x01 << SCL;
  DDRC |= 0x01 << SDA;

  PORTC |= 0x01 << SCL;
  PORTC |= 0x01 << SDA;
}

void I2C_start()
{
  PORTC &= ~(0x01 << SDA);  //SDA LOW
  PORTC &= ~(0x01 << SCL);  //SCL LOW
}

void I2C_stop()
{
  PORTC &= ~(0x01 << SDA);  //SDA LOW
  PORTC |= 0x01 << SCL;
  PORTC |= 0x01 << SDA;
}

void data_8bit_set(char data)
{
  for(int i = 0; i < 8; i++)
  {
    if(data & 0x01 << (7 - i))
    {
      //digitalWrite(SDA, HIGH);
      PORTC |= 0x01 << SDA;
    }
    else
    {
      //digitalWrite(SDA, LOW);
      PORTC &= ~(0x01 << SDA);
    }

    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }
}

void I2C_ack()
{
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
}

void I2C_byte_write(char addr, char data)
{
  I2C_start();
  data_8bit_set(addr << 1);
  I2C_ack();
  data_8bit_set(data);
  I2C_ack();
  I2C_stop();
}
