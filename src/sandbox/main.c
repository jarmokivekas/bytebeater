#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

//ringbuffer for USART ISR
#define TX_buffer_len 0xff
char UART_TX_buffer[TX_buffer_len];
char *UART_TX_curr;
char *UART_TX_last;

//this is the ISR that UART_puts will use
ISR(USART_UDRE_vect){
	UDR0 = *UART_TX_curr;
	if(UART_TX_curr == UART_TX_last){
		//we reached the end of buffered output, disable the vector
		UCSR0B &= ~(1<<UDRIE0);
	} else {
		UART_TX_curr++;
		//if we're at the last char, go back to the beginning
		if(UART_TX_curr == &UART_TX_buffer[TX_buffer_len]){
			UART_TX_curr = UART_TX_buffer;
		}
	}
}

void UART_puts(char *S){
	//add S to the ringbuffer
	while(*S != 0x00){
		//UART_TX_curr++ = *S++;
		*UART_TX_last = *S;
		UART_TX_last++;
		S++;
		//if we go to far, return to start of ring
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

void setup_puts(){
	setup_UART();
	//set global TX varialbes and disable interrupt
	UART_TX_last = UART_TX_buffer;
	UART_TX_curr = UART_TX_buffer;
	UCSR0B &= ~(1<<UDRIE0);
	//call sei() after ths function to start the buffered writer
}

int main(){
	setup_puts();
	sei();
	UART_puts("Hello computer!\n\r");
	UART_puts("Good morning programmer!\n\r");
	UART_puts("What a wonderful world!\n\r");
	UART_put_hex(0xDE);
	UART_put_hex(0xAD);
	UART_put_hex(0xBE);
	UART_put_hex(0xEF);
	UART_puts("How fast and how much do i have to write in the buffer before i start getting glitches? I'd imagine that at some point the UART_TX_last will reach UART_TX_curr and then we'll miss 255 chars of output.");
	while(1);
}

