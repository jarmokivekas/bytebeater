#ifndef timer_h
#define timer_h

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../language/interpreter.h"

//sets up the timer and saves the context pointer for later
int timer_setup(beat_context* ctx);

#endif /*timer_h*/
