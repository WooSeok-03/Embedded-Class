#include<Wire.h>

void setup() {
  Wire.begin();         // Join i2c bus ( Master로 I2C 초괴화 )
  Serial.begin(9600);   // Start Serial for Output
}

//byte x = 0;

void loop() {
//  Wire.beginTransmission(4);  // Address 4 Slave로 전송
//  Wire.write(x);              // Sends one byte;
//  Wire.endTransmission();     // Stop Transmitting
//  x++;
//  delay(500);

  // Receive (Slave에서 "Hello "를 받음.)
//  Wire.requestFrom(8,6);    // Address 8 Slave에 6byte 데이터 요청
//  while(Wire.available())   // Slave may send less than requested
//  {
//    char c = Wire.read();   // receive a byte as character
//    Serial.print(c);        // print the character
//  }

  if(Serial.available())
  {
    String str = Serial.readString();
    char* buf = str.c_str();
    
    Wire.beginTransmission(8);
    Wire.write(buf);
    Wire.endTransmission();

    if(strcmp(buf, "temp") == 0 || strcmp(buf, "humi") == 0 || strcmp(buf, "jodo") == 0) 
    {
      Wire.requestFrom(8, 1);
      while(Wire.available()) 
      {
        Serial.println((int) Wire.read());
      }
    }
    
    delay(500);
    Serial.println(buf);
  }
}
