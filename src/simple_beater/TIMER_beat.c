#include "TIMER_beat.h"

void setup_TIMER(){
	/**
	* We will be using OCR1A as our PWM output which is the
	* same pin as PD6.
	*/
	DDRD |= _BV(PD6);
	 
	/**
	* There are quite a number of PWM modes available but for the
	* sake of simplicity we'll just use the 8-bit Fast PWM mode.
	* This is done by setting the WGM00 and WGM01 bits.
	*/
	TCCR0A |= _BV(WGM00) | _BV(WGM01);

	/**
	* Setting COM0A1 tells the microcontroller to set the
	* output of the OCR0A pin low when the timer's counter reaches
	* a compare value (which will be explained below). 
	*/
	TCCR0A |= _BV(COM0A1);

	/**
	* CS00 being set simply turns the timer on without a prescaler (so at full
	* speed). The timer is used to determine when the PWM pin should be
	* on and when it should be off.
	*/
	TCCR0B |= _BV(CS00);
	
	/**
	* We want to catch the timer overflow interrupt TIMER0_OVF so we
	* set TOIE0.
	*/
	TIMSK0 |= _BV(TOIE0);

	/**
	* Global interrupts must be enabled catch TOIE0.
	* Call sei() after this function
	*/
}

//ISR callback function code and data
volatile context* ctx;
uint8_t sample(){
	return ctx->t<<1 & ctx->t>>4 & ctx->analog_1;
}

ISR(TIMER0_OVF_vect){
	ctx->t_phase++;
	if(ctx->t_phase >= ctx->t_velocity){
		ctx->t_phase = 0;
		ctx->t++;
		OCR0A = sample(ctx);
	}
}

void setup_bytebeat(volatile context* ctx_in){
	setup_TIMER();
	ctx = ctx_in;
}
