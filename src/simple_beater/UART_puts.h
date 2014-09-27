#ifndef UART_puts_h
#define UART_puts_h

#include <avr/io.h>
#include <avr/interrupt.h>

void UART_puts(char *S);
void UART_put_hex(uint8_t n);
void setup_UART_puts();

#endif /*UART_puts_h*/
