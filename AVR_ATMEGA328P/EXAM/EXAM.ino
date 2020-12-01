#include <stdio.h>
#include "OLED.h"
#include "I2C_LCD.h"
#include "PWM.h"
#include "ultrasonic.h"
#include "remocon.h"
#include "servo.h"
#include "joystick.h"

enum {
  c_servo, c_pwm, c_ultra, c_input, c_i2c, c_remocon
};

char key;
char x = 40;
char y = 5;

char buf[100];

unsigned long c_millis = 0;
unsigned long ultra_p_millis = 0;

char x_left = 0;
char x_right = 0;

bool ultrasonic_on = false;
bool input_on = false;
bool remocon_on = false;
bool pwm_on = false;
bool i2c_on = false;
bool servo_on = false;

bool first_remocon = true;

char pre_distance = 0;
char cur_distance = 0;
char pre_font = 0;
char remocon_value = 0;
char pre_remocon_value = 0;

char c_choice = 0;

void setup()
{
  Serial.begin(115200);
  oled_set();
  PWM_setup();
  ultrasonicInit();
  remoconInit();
  i2c_init();
  servo_init();
  adc_init();

  pinMode(JOY_BUTTON, INPUT_PULLUP);
}

void loop()
{
  int joy_button = digitalRead(JOY_BUTTON);
  int x_joy = analog_read(AD_0);

  c_millis = millis();

  if (x_joy > 0 && x_joy < 400)
  {
    if (x_left == 0)
    {
      x_left = 1;
      c_choice++;
      move_choice();
    }
  }
  else if (x_joy > 600 && x_joy < 1023)
  {
    if (x_right == 0)
    {
      x_right = 1;
      c_choice--;
      move_choice();
    }
  }
  else if (x_joy > 400 && x_joy < 600)
  {
    x_left = 0;
    x_right = 0;
  }

  if (joy_button == 0)
  {
    all_off();
    if (c_choice == c_servo) servo_on = true;
    else if (c_choice == c_pwm) pwm_on = true;
    else if (c_choice == c_ultra) ultrasonic_on = true;
    else if (c_choice == c_input) input_on = true;
    else if (c_choice == c_remocon) remocon_on = true;
    else if (c_choice == c_i2c) i2c_on = true;
    else if (c_choice == c_servo) servo_on = true;
  }


  if (Serial.available())
  {
    key = Serial.read();
    if (key == 'a')
    {
      delete_rect(x, y);
      c_choice--;
      move_choice();
    }
    else if (key == 'd')
    {
      delete_rect(x, y);
      c_choice++;
      move_choice();
    }
    else if (key == ' ')
    {
      all_off();
      if (c_choice == c_servo) servo_on = true;
      else if (c_choice == c_pwm) pwm_on = true;
      else if (c_choice == c_ultra) ultrasonic_on = true;
      else if (c_choice == c_input) input_on = true;
      else if (c_choice == c_remocon) remocon_on = true;
      else if (c_choice == c_i2c) i2c_on = true;
      else if (c_choice == c_servo) servo_on = true;
    }

    if (input_on == true)
    {
      font_write(60, 55, WHITE, pre_font);
      font_write(60, 55, BLACK, key);
      pre_font = key;
    }
  }

  if (pwm_on == true) TIMSK1 = 0x02;
  if (servo_on == true) TIMSK3 = 0x03;
  if (i2c_on == true) backlightONOFF(c_millis);
  
  if (ultrasonic_on == true)
  { 
    if(c_millis - ultra_p_millis > 500)
    {
      ultra_p_millis = c_millis;

      ultrasonicTrigger(c_millis);
      pre_distance = cur_distance;
      cur_distance = getDistance();
      
      if (pre_distance != cur_distance) string_write(35, 55, WHITE, buf);
      sprintf(buf, "%d", cur_distance);
      string_write(35, 55, BLACK, buf);
    }
  }

  if (remocon_on == true)
  {
    if(first_remocon) clear_string();
    first_remocon = false;
    pre_remocon_value = remocon_value;
    remocon_value = getRemoconNum();
    if (pre_remocon_value != remocon_value) font_write(60, 55, WHITE, pre_remocon_value);
    font_write(60, 55, BLACK, remocon_value);
  }

  
}

void all_off()
{
  clear_string();
  input_on = false;
  ultrasonic_on = false;
  remocon_on = false;
  pwm_on = false;
  i2c_on = false;
  servo_on = false;
  TIMSK1 = 0x00;
  TIMSK3 = 0x00;
  light_off();
  PORTB &= ~(LED);
}

void move_choice()
{
  delete_rect(x, y);
  if (c_choice == -1) c_choice = c_remocon;
  else if (c_choice > 5) c_choice = c_servo;

  if (c_choice == c_servo)
  {
    x = 37;
    y = 5;
    make_rect(x, y);
  }
  else if (c_choice == c_pwm)
  {
    x = 84;
    y = 5;
    make_rect(x, y);
  }
  else if (c_choice == c_ultra)
  {
    x = 112;
    y = 33;
    make_rect(x, y);
  }
  else if (c_choice == c_input)
  {
    x = 84;
    y = 85;
    make_rect(x, y);
  }
  else if (c_choice == c_i2c)
  {
    x = 37;
    y = 85;
    make_rect(x, y);
  }
  else if (c_choice == c_remocon)
  {
    x = 7;
    y = 35;
    make_rect(x, y);
  }
}
