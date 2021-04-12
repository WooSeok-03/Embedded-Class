#include "uart.h"

void setup() {
  Serial.begin(9600);
  uart_init(9600);
}

char buf[50];
int a = 0;
int b = 0;

void loop() {
  uart_tx(0x31);
  uart_tx_string("Hello\n");

  sprintf(buf, "hello = %d\n", a++);
  uart_tx_string(buf);

  printfh("I'm Wooseok %d\n", b++);
  
  delay(1000);
}
