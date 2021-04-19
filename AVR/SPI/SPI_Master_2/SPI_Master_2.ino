/* **********************
 * (2) Master의 Serial 모니터에서 입력 받은 데이터 Slave로 전송
 * **********************/

#include<SPI.h>

// Master Code
void setup() {
  SPI.begin();            // SPI 활성화
  digitalWrite(SS, HIGH); // Slave 미선택 초기화 ( LOW : 선택 / HIGH : 미선택 )
  pinMode(SS, OUTPUT);
  
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  Serial.begin(9600);
}

char serial_data;

void loop() {
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));

  if(Serial.available())
  {
    serial_data = Serial.read();
    digitalWrite(SS, LOW); 
    char serial_rxData = SPI.transfer(serial_data);
    digitalWrite(SS, HIGH);
    Serial.print(serial_data); 
  }
  SPI.endTransaction();
}
