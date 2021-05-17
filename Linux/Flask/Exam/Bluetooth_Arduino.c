#include <SoftwareSerial.h>
#include <string.h>
#include <DHT11.h>

#define BT_RXD 8
#define BT_TXD 7
#define DHTPIN A0

DHT11  dht11(DHTPIN);
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(38400);
  pinMode(DHTPIN, INPUT);
}

unsigned long c_millis = 0;
unsigned long p_millis = 0;

void loop() {
  c_millis = millis();

  if (c_millis - p_millis > 500)
  {
    p_millis = c_millis;

    if (!bluetooth.available())
    {
      double temp;
      double humi;
      dht11.read(humi, temp);
      
      String add = "TEMP:" + String(temp) + " HUMI:" + String(humi);
      char send_data[100];
      strcpy(send_data, add.c_str());
      
      Serial.println(send_data);
      bluetooth.write(send_data);
    }
  }
}