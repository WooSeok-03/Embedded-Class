#include "Test.h"
#include "Remocon.h"
#include "ultrasonic.h"

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
  /*
  Serial.println("Hello");
  Serial.println(counting());
  delay(1000);
  */

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
