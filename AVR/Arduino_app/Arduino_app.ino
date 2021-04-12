/*
#include "Test.h"
#include "Remocon.h"
#include "ultrasonic.h"
#include "I2C_back.h"

#define REMOCON_PIN 2
#define ULTRASONIC_ECHO_PIN 3
#define ULTRASONIC_TRIGGER_PIN 4

float ultrasonic_dist = 0;
char remocon_number = 0;

unsigned long c_millis = 0;
unsigned long p_millis_ultra = 0;

void setup() {
  Serial.begin(9600);
  remocon_init(REMOCON_PIN);  //arduino pin 2
  ultrasonic_init(ULTRASONIC_ECHO_PIN, ULTRASONIC_TRIGGER_PIN);  //arduino pin 3, 4

  // PCF8576
  I2C_init();
  while(1)
  {
    I2C_byte_write(0x27, 0x08);
    delay(1000);
    I2C_byte_write(0x27, 0x00);
    delay(1000);
  }
  
}

void loop() {
  //Serial.println("Hello");
  //Serial.println(counting());
  //delay(1000);
  

  c_millis = millis();

  if(c_millis - p_millis_ultra > 1000)
  {
    p_millis_ultra = c_millis;

    ultrasonic_trigger();
  }

  //Ultrasonic Callback function
  if(ultrasonic_callback(&ultrasonic_dist))
  {
    p_millis_ultra = c_millis;
    Serial.print("UltraSonic : ");
    Serial.println(ultrasonic_dist);
  }

  //Remocon Callback function
  if(remocon_callback(&remocon_number))
  {
    int_callback_flag_clear();
    Serial.print("Remocon : ");
    Serial.println(remocon_number);
  }
}
*/

/*
#include "char_LCD.h"
#include "I2C.h"
#include "PCF8574_LCD.h"

#define SCL 18
#define SDA 19

char char_lcd_pin_8bit[11] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
char char_lcd_pin_4bit[7] = { 3, 4, 5, 10, 11, 12, 13 };

unsigned long current_millis = 0;
unsigned long current_micros = 0;

void setup()
{
    Serial.begin(9600);

    //char_lcd_8bit
    //char_lcd_init_8bit(char_lcd_pin_8bit);

    //char_lcd_4bit
    char_lcd_inst_4bit(char_lcd_pin_4bit);

    //I2C
    I2C_init(SCL, SDA);
}

void loop()
{
    //8bit data
    //char_lcd_data_8bit(0x31);

    //4bit data
    //char_lcd_inst_4bit(0x31);

    //delay(1000);

    current_millis = millis();
    current_micros = micros();

    PVF8574_LCD_backlight_PWM(current_millis, current_micros, 10);
}
*/

/*
#include "74595.h"

#define CLK_74595   14
#define DATA_74595  15
#define LATCH_74595 16

#define PWM_PIN_74595   3
#define CYCLE_PWM_74595 20

void setup()
{
    Serial.begin(9600);
    init_74595(CLK_74595, DATA_74595, LATCH_74595);
}

unsigned long current_millis = 0;
unsigned long current_micros = 0;
unsigned long previous_millis = 0;
unsigned long previous_micros = 0;

void loop()
{
    //set_data_74595(0x01);
    //delay(1000);
    //set_data_74595(0x01);
    //delay(1000);

    current_micros = micros();
    current_millis = millis();

    PWM_74595(current_millis, current_micros, PWM_PIN_74595, CYCLE_PWM_74595);

    if (current_millis - previous_millis > 1000)
    {
        previous_millis = current_millis;
        lcd_data_4bit_74595(0x31);
    }
}
*/

/*
#include"servo.h"

#define SERVO_PORT 4

unsigned long c_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;
unsigned char servo_degree = 22;
unsigned int servo_duty = 0;
int servo_duty2 = 0;

void setup()
{
  Serial.begin(9600);
  servo_init(SERVO_PORT);
}

int servo_positions = 0;

void loop()
{
//  servo_position(servo_positions);
//
//  servo_positions++;
//  if (servo_positions == 180) servo_positions = 0;

  c_micros = micros();
  c_millis = millis();

  if(c_millis - p_millis > 30)
  {
    p_millis = c_millis;
    
    //servo_degree++;
    //if(servo_degree == 180) servo_degree = 0;
    //servo_duty = (int)(700 + (int)(((float)(180 - servo_degree) / 180.0) * 1600) / 32 + 0.5); //servo_duty : 22 ~ 72

    servo_duty++;
    if(servo_duty == 72) servo_duty = 22;
  }

  servo_position_micros(servo_duty, c_micros);
}
*/

/*
#include "gpio.h"

void setup()
{
  Serial.begin(9600);

  //pinMode(13, OUTPUT);
  //DDRD |= 0x20;
  
  //pin_mode(13, OUTPUT);
  pin_mode(2, INPUT);
}

void loop()
{
  
  //digitalWrite(13, HIGH);
  //delay(1000);
  //digitalWrite(13, LOW);
  //delay(1000);

  //PORTD |= 0x20;
  //delay(1000);
  //PORTD & ~0x20);
  //delay(1000);
  
  //digital_write(13, HIGH);
  //delay(1000);
  //dgital_write(13, LOW);
  //delay(1000);

  int in_value = digital_read(2);

  Serial.printf("in_value = %d\n",in_value);
  delay(100);
}
*/

/*
#include "fnd.h"

//FND : A, B, C, D, E, F, G, DP
char fnd_pin_1[8] = {4, 5, 6, 7, 8, 9, 10, 11};
//FND : A, B, C, D, E, F, G, DP, Power, common1(1000), common2(100), common3(10), common4(1)
char fnd_pin_2[10] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};  //2자리 수

char fnd_pin[12] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

void setup()
{
  Serial.begin(9600);
  //fnd_init_1(fnd_pin_1, C_CATHODE);
  //fnd_init_2(fnd_pin_1, C_CATHODE);
  fnd_init(4, fnd_pin, C_CATHODE);
}

unsigned long c_millis = 0;
int fndNumber = 1234;
unsigned long p_millis_1s = 0;

void loop()
{
  c_millis = millis();
  fnd_num_millis(c_millis, 1234);

  if(c_millis - p_millis_1s > 1000)
  {
    p_millis_1s = c_millis;
    fndNumber++;
  }
  
  //fnd_num_1(2);
  //delay(1000);
  //fnd_num_1(3);
  //delay(1000);

  //fnd_num_2(23);
}
*/
