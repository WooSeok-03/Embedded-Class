#include<Wire.h>
#include "DHT.h"
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


DHT dht(5, DHT11);


// [ Handler Function ]
// Return Value : void
// Paramiter : int

//void receiveEvent(int howMany)
//{
//  while(Wire.available() > 0)
//  {
//    char c = Wire.read();
//    Serial.println(c);
//  }
//}

// Recevie (Master에 "Hello "를 보냄.)
//void requestEvent()
//{
//  Wire.write("Hello ");
//}

int flag = 0;
int str_len = 0;
char buf[100];

unsigned long c_millis = 0;
unsigned long p_millis = 0;

int temp = 0;
int humi = 0;
int jodo = 0;

int request = 0;

void requestEvent() {
  if(request == 1) Wire.write(temp);
  else if(request == 2) Wire.write(humi);
  else if(request == 3) Wire.write(jodo);
}
void receiveEvent(int howMany)
{
  int idx = 0;
  while (Wire.available() > 0)
  {
    char c = Wire.read();
    buf[idx++] = c;
    buf[idx] = 0;
    Serial.println(c);
  }
  flag = 1;

  if (strcmp(buf, "temp") == 0) request = 1;
  else if (strcmp(buf, "humi") == 0) request = 2;
  else if (strcmp(buf, "jodo") == 0) request = 3;
  // Sensor값을 받을때, lcd를 출력X
  //  else
  //  {
  //    flag = 0;
  //    c_millis = millis();
  //  }
}

void setup() {
  //  Wire.begin(4);                // Address 4번 Slave 동작 초기화
  //  Wire.onReceive(receiveEvent); // Register Event
  //  Serial.begin(9600);           // Start Serial for Output

  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  
  dht.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  // LCD Test
  lcd.setCursor(0, 0);
  lcd.print("ASDF");
}

void loop() {
  c_millis = millis();
  if(c_millis - p_millis >= 1000) 
  {
    p_millis = c_millis;
    temp = dht.readTemperature();
    humi = dht.readHumidity();
    jodo = analogRead(A0);
  }
  if (flag) 
  {
    flag = 0;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(buf);
  }
}
