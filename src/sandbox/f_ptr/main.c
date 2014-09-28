#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "callback.h"

void blink(uint8_t mask){
	PORTB ^= mask;
	_delay_ms(1000);
	PORTB ^= mask;
	_delay_ms(1000);
}

int main(){
	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	blink(0x01);

	//set the ISR callback function
	set_callback(blink, 0x02);
	
	//INT0 interrupt triggers on rising edge
	EICRA |= (1<<ISC01) | (1<<ISC00);
	EIMSK |= (1<<INT0);
	sei();

	//trigger the interrupt in software--------BEEP BEEP BEEP
	DDRD |= (1<<DDD2);
	PORTD |= (1<<PD2);
	PORTD &= ~(1<<PD2);
	
	blink(0x04);
	return 0;
}
