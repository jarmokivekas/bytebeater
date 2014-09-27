#include "timer.h"

void timer0_PWM_init(/*options?*/){
	//what we set    : why we do it
	//DDB0           : make direction of portB0 output (pin5, OC0A)
	DDRB |= (1<<DDB0);
	
	//WGM00 and WGM01: make the timer0 work in WaveGenerationMode (fast PWM)
	//COM0A1         : clear OC0A (pin5) on compare match and set it on overflow
    //COM0B1         : to use OC0B (pin6) as well
    TCCR0A |= (1<<WGM00)|(1<<WGM01)|(1<<COM0A1); 
    //CS00           : no clock prescaler
    TCCR0B |= (1<< CS00);
 
 	//enable the overflow interrupt mask and flag
 	TIMSK0 |= (1<<TOIE0);
 	TIFR0 |= (1<<TOV0);

    //50% duty cycle
    OCR0A = 128;
    // initialize counter.
    TCNT0 = 0;
}

//there has to be a public context in order for the ISR to access it
//the public variable will not be accessed from other files
beat_context* ctx_p;
int pulse;	//the amount of samples since last t change

int timer_setup(beat_context* ctx){
	ctx_p = ctx;
	timer0_PWM_init();
	return 0;
}

//Timer 0 overflow vector
ISR(TIMER0_OVF_vect){
    pulse++;
	//compare pulses against the velocity of t
    if( pulse <= ctx_p->t_v ){
        pulse = 0;
        ctx_p->t++;
        OCR0A = evaluate(ctx_p);
    }
}
