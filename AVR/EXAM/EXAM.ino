#include <stdio.h>
#include "OLED.h"
#include "I2C_LCD.h"
#include "PWM.h"
#include "ultrasonic.h"
#include "remocon.h"
#include "servo.h"
#include "joystick.h"
#include "keypad.h"

enum {
  c_servo, c_pwm, c_ultra, c_input, c_i2c, c_remocon
};

char key;
char pre_key;
char x = 40;
char y = 5;

int joy_button = 0;
int x_joy = 0;
int y_joy = 0;

char mouse_x = 0;
char mouse_y = 0;

char key_in;
char pre_key_in = 0;
char key_toggle = 0;

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
bool select_on = true;

bool first_remocon = true;
bool servo_menu = true;

bool remocon_menu = true;
int remocon_menu_value;
int pre_remocon_menu_value;
char remocon_menu_toggle = 0;

char pre_distance = 0;
char cur_distance = 0;
char pre_font = 0;
char remocon_value = 0;
char pre_remocon_value = 0;

char c_choice;

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
  keypadInit();
}

void loop()
{
  mouse_set();

  c_millis = millis();

  mouse_move(x_joy, y_joy, joy_button);
  keypad_menu_control();
  menu_remocon_control();

  if (Serial.available())
  {
    key = Serial.read();
    if (key == 'a')
    {
      c_choice--;
      move_choice();
    }
    else if (key == 'd')
    {
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
    }

    if (key >= '1' && key <= '6')
    {
      if (pre_key != key) all_off();
      if (key == '1') servo_on = true;
      else if (key == '2') pwm_on = true;
      else if (key == '3') ultrasonic_on = true;
      else if (key == '4') input_on = true;
      else if (key == '5') i2c_on = true;
      else if (key == '6') remocon_on = true;
      pre_key = key;
    }

    if (input_on)
    {
      if (select_on) draw_selection_click(c_input);
      select_on = false;
      font_write(60, 55, WHITE, pre_font);
      font_write(60, 55, BLACK, key);
      pre_font = key;
    }
  }

  if (pwm_on)
  {
    if (select_on) draw_selection_click(c_pwm);
    select_on = false;
    TIMSK1 = 0x02;
  }

  if (servo_on == true)
  {
    if (select_on) draw_selection_click(c_servo);
    select_on = false;
    TIMSK3 = 0x03;
  }

  if (i2c_on)
  {
    if (select_on) draw_selection_click(c_i2c);
    select_on = false;
    backlightONOFF(c_millis);
  }

  if (ultrasonic_on)
  {
    if (select_on) draw_selection_click(c_ultra);
    select_on = false;
    if (c_millis - ultra_p_millis > 500)
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

  if (remocon_on)
  {
    remocon_menu = false;
    if (select_on) draw_selection_click(c_remocon);
    select_on = false;
    if (first_remocon) clear_string();
    first_remocon = false;
    pre_remocon_value = remocon_value;
    remocon_value = getRemoconNum();
    if (remocon_value - 0x30 == 15 || remocon_value - 0x30 == 16 || remocon_value - 0x30 == 17) remocon_menu = true;
    if (pre_remocon_value != remocon_value) font_write(60, 55, WHITE, pre_remocon_value);
    font_write(60, 55, BLACK, remocon_value);
  }
}

void all_off()
{
  clear_string();
  delete_selection_click();
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
  select_on = true;
  remocon_menu = true;
}

void mouse_set()
{
  joy_button = digitalRead(JOY_BUTTON);
  x_joy = analog_read(AD_0);
  y_joy = analog_read(AD_1);
}

void move_choice()
{
  delete_rect(x, y);
  if (c_choice < 0) c_choice = c_remocon;
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

void mouse_move(int x_joy, int y_joy, int joy_button)
{
  if (x_joy > 0 && x_joy < 400)
  {
    mouse_x += 4;
    if (mouse_x > 117) mouse_x = 117;
    mouse_pointer_move(mouse_x, mouse_y, c_choice);
  }
  else if (x_joy > 600 && x_joy < 1024)
  {
    mouse_x -= 4;
    if (mouse_x < 0) mouse_x = 0;
    if (servo_on || pwm_on || ultrasonic_on || input_on || remocon_on || i2c_on) draw_selection_click(c_choice);
    mouse_pointer_move(mouse_x, mouse_y, c_choice);
  }

  if (y_joy > 0 && y_joy < 400)
  {
    mouse_y += 4;
    if (mouse_y > 111) mouse_y = 111;
    if (servo_on || pwm_on || ultrasonic_on || input_on || remocon_on || i2c_on) draw_selection_click(c_choice);
    mouse_pointer_move(mouse_x, mouse_y, c_choice);
  }
  else if (y_joy > 600 && y_joy < 1024)
  {
    mouse_y -= 4;
    if (mouse_y < 0) mouse_y = 0;
    if (servo_on || pwm_on || ultrasonic_on || input_on || remocon_on || i2c_on) draw_selection_click(c_choice);
    mouse_pointer_move(mouse_x, mouse_y, c_choice);
  }

  if (joy_button == 0)
  {
    all_off();
    selection_state();
  }
}

void keypad_menu_control()
{
  keyInput(c_millis);
  key_in = getInputNumber();

  if (pre_key_in != key_in) all_off();
  if (key_in == 1) servo_on = true;
  else if (key_in == 2) pwm_on = true;
  else if (key_in == 3) ultrasonic_on = true;
  else if (key_in == 5) input_on = true;
  else if (key_in == 6) i2c_on = true;
  else if (key_in == 7) remocon_on = true;
  pre_key_in = key_in;

  if (key_in == 9)
  {
    c_choice--;
    move_choice();
  }
  else if (key_in == 10)
  {
    c_choice++;
    move_choice();
  }
  else if (key_in == 11)
  {
    if (pre_key_in != key_in) all_off();

    if (c_choice == c_servo) servo_on = true;
    else if (c_choice == c_pwm) pwm_on = true;
    else if (c_choice == c_ultra) ultrasonic_on = true;
    else if (c_choice == c_input) input_on = true;
    else if (c_choice == c_remocon) remocon_on = true;
    else if (c_choice == c_i2c) i2c_on = true;
  }
}

void menu_remocon_control()
{
  if (remocon_menu)
  {
    remocon_menu_value = remocon_menu_control();

    if (remocon_menu_value == 15)
    {
      if (remocon_menu_toggle == 0)
      {
        remocon_menu_toggle = 1;
        c_choice--;
        move_choice();
      }
    }
    else if (remocon_menu_value == 16)
    {
      if (remocon_menu_toggle == 0)
      {
        remocon_menu_toggle = 1;
        c_choice++;
        move_choice();
      }
    }
    else if (remocon_menu_value == 17)
    {
      if (remocon_menu_toggle == 0)
      {
        all_off();

        remocon_menu_toggle = 1;
        if (c_choice == c_servo) servo_on = true;
        else if (c_choice == c_pwm) pwm_on = true;
        else if (c_choice == c_ultra) ultrasonic_on = true;
        else if (c_choice == c_input) input_on = true;
        else if (c_choice == c_remocon) remocon_on = true;
        else if (c_choice == c_i2c) i2c_on = true;
      }
    }
    else if (remocon_menu_toggle == 1) remocon_menu_toggle = 0;
    else
    {
      if (remocon_menu_value != 0)
      {
        all_off();
        if (remocon_menu_value == 1) servo_on = true;
        else if (remocon_menu_value == 2) pwm_on = true;
        else if (remocon_menu_value == 3) ultrasonic_on = true;
        else if (remocon_menu_value == 4) input_on = true;
        else if (remocon_menu_value == 5) i2c_on = true;
        else if (remocon_menu_value == 6) remocon_on = true;
      }
    }
  }
}

void selection_state()
{
  c_choice = selection_area(mouse_x, mouse_y);
  if (c_choice == c_servo) servo_on = true;
  else if (c_choice == c_pwm) pwm_on = true;
  else if (c_choice == c_ultra) ultrasonic_on = true;
  else if (c_choice == c_input) input_on = true;
  else if (c_choice == c_remocon) remocon_on = true;
  else if (c_choice == c_i2c) i2c_on = true;
}
