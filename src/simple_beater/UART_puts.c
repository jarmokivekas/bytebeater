/*
*Interrupt based UART printing functions for AVR atmega328p
*Juha Kivekäs
*Get to know the structure of a ring buffer to understand glitches that might occur.
*/


#include "UART_puts.h"

//ringbuffer for USART ISR
#define TX_buffer_len 0xff
char UART_TX_buffer[TX_buffer_len];
char *UART_TX_curr;
char *UART_TX_last;

//this is the ISR that UART_puts will use to send data
ISR(USART_UDRE_vect){
	//send next char in buffer
	UDR0 = *UART_TX_curr;
	UART_TX_curr++;

	//if we're at the last char of the ring, go back to the beginning
	if(UART_TX_curr == &UART_TX_buffer[TX_buffer_len]){
		UART_TX_curr = UART_TX_buffer;
	}

	//if we reached the end of buffered output, disable this interrupt vector
	if(UART_TX_curr == UART_TX_last){
		UCSR0B &= ~(1<<UDRIE0);
	}
}

//XXX: writng to the ringbuffer too fast will make you lose data
void UART_puts(char *S){
	//add S to the ringbuffer
	while(*S != 0x00){
		*UART_TX_last = *S;
		UART_TX_last++;
		S++;
		//if we reach the end of the ring, return to start of ring
		if(UART_TX_last == &UART_TX_buffer[TX_buffer_len]){
			UART_TX_last = UART_TX_buffer;
		}
	}
	//enable interrupt
	UCSR0B |= (1<<UDRIE0);
}

void UART_put_hex(uint8_t n){
	char S[4];
	uint8_t nibble;

	//high nibble
	nibble =(n & 0xf0) >> 4;
	if(nibble < 0xa)
		S[0] = '0' + nibble;
	else
		S[0] = 'A' + (nibble - 10);
	
	//low nibbble
	nibble = n & 0x0f;
	if(nibble < 0xa)
		S[1] = '0' + nibble;
	else
		S[1] = 'A' + (nibble - 10);

	S[2] = 0x00;
	UART_puts(S);
}

void setup_UART() {
	// configure the ports speed
	// 9600 baud at 16MHz , 100.16% accuracy
	UBRR0H = 0x00;
	UBRR0L = 103;
	 
	// asynchronous, 8N1 mode 8-bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);

	// rx/tx enable
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
}

void setup_UART_puts(){
	setup_UART();
	//set global TX varialbes and disable interrupt
	UART_TX_last = UART_TX_buffer;
	UART_TX_curr = UART_TX_buffer;
	UCSR0B &= ~(1<<UDRIE0);
	//XXX: call sei() after ths function to start the buffered writer
}
