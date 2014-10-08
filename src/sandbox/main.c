#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(){
	volatile uint8_t a = 13;
	volatile uint8_t b = 24;
	volatile uint8_t c = a * b;
	return c;
}
