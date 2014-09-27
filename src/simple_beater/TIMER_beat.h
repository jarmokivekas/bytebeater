#ifndef TIMER_pwm_h
#define TIMER_pwm_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include "context.h"

void setup_TIMER();
void setup_bytebeat(volatile context* ctx_in);

#endif /*TIMER_pwm_h*/
