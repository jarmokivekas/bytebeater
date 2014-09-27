#include "log.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

void setup_print(){
	// Turn on the transmission and reception circuitry
	UCSRB |= (1 << RXEN); //| (1 << TXEN);
	// Use 8-bit character sizes
	UCSRC |= (1 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1); 
	 
	// Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRRL = BAUD_PRESCALE;
	// Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRRH = (BAUD_PRESCALE >> 8);
}

void print(int type, char* S){
	//serial.write(S)?
}
