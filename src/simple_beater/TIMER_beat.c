#include "TIMER_beat.h"

void setup_TIMER0_PWM(){
	//We will be using OCR1A as our PWM output which is the
	//same pin as PD6.
	DDRD |= (1<<PD6);
	 
	//There are quite a number of PWM modes available but for
	//preformance we'll use the 8-bit Fast PWM mode.
	//This is done by setting the WGM00 and WGM01 bits.
	TCCR0A |= (1<<WGM00) | (1<<WGM01);

	//Setting COM0A1 tells the microcontroller to set the
	//output of the OCR0A pin low when the timer's counter reaches
	//a compare value (which will be explained below).
	TCCR0A |= (1<<COM0A1);

	//CS00 being set simply turns the timer on without a prescaler (full speed)
	TCCR0B |= (1<<CS00);
}

void setup_TIMER1_CTC(){
	TCCR1B |= (1<<CS10);	//no prescaler
	TCCR1B |= (1<<WGM12);	//CTC with OCR1A
	TIMSK1 |= (1<<OCIE1A);	//unmask output compare interrupt
	//call sei() to enable timer interrupt
}

uint8_t t = 0;
ISR(TIMER1_COMPA_vect){
	//PORTB ^= (1<<PB0);
	t+=2;
	OCR0A = (t&2)?t:0xff-t;
}
