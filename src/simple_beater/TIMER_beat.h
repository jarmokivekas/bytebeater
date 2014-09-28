#ifndef TIMER_pwm_h
#define TIMER_pwm_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include "context.h"

void setup_TIMER0_PWM();
void setup_TIMER1_CTC();
void setup_beat(volatile beat_context *ctx_in);

#endif /*TIMER_pwm_h*/
