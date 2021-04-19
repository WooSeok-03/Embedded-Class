/* **********************
 * (2) Master의 Serial 모니터에서 입력 받은 데이터 Slave로 전송
 * **********************/

#include<SPI.h>

byte count;

// Slave Code
void setup() {
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  SPI.setClockDivider(SPI_CLOCK_DIV16); // Master와 동일 1MHz

  SPCR |= _BV(SPE);     // SPCR 레지스터 설정 SPI 활성화
  SPCR &= ~_BV(MSTR);   // Slave Mode 설정
  SPCR |= _BV(SPIE);    // Interrupt 허용

  Serial.begin(9600);
}

char input_data;

ISR(SPI_STC_vect) // SPI Serial Transfer Complete
{
  input_data = SPDR;
  Serial.print(input_data);
}

void loop() {
  
}
