#include "TIMER_pwm.h"

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



//TIMER0 overflow vector callback function and argument data.
//uint8_t (*sample)(context* c);
context* ctx;

ISR(TIMER0_OVF_vect){
	uint16_t t;
	ctx->t_p++;
	if(ctx->t_p >= ctx->t_v){
		ctx->t_p = 0;
		ctx->t++;
		t = ctx->t;
		OCR0A = (t>>4)&t&ctx->a;
	}
}

void setup_bytebeat(/*uint8_t (*sample_)(context*), */context* ctx_){
	//sample = sample_;
	ctx = ctx_;
}
