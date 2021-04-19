/* **********************
 * (1) Master => Slave로 임의의 데이터 보내기
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

  digitalWrite(SS, LOW);            // Slave 선택
  char rxData = SPI.transfer(0x31); // Data 전송 및 수신 (0x31 : 1 전송)
  digitalWrite(SS, HIGH);           // Slave 선택 헤제
  Serial.println(rxData);
  
  SPI.endTransaction();
}
