#ifndef UART_H
#define UART_H

#include "Arduino.h"

void uart_init(unsigned int baudrate);
void uart_tx(char data);
void uart_tx_string(char *string);
void uart_rx();
void printfh(char *format, ...);


#endif
