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

volatile beat_context *ctx;
ISR(TIMER1_COMPA_vect){
	ctx->t++;
	uint16_t t = ctx->t;
	OCR0A = t;//(t<<1)&(t>>4)?0x00:0xff;
}

void setup_beat(volatile beat_context *ctx_in){
	ctx = ctx_in;
}
