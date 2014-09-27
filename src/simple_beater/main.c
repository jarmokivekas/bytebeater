/**
* A simple version of the bytebeater for the ATmega328P.
* Building for AVR on Arduino UNO:
* 
* avr-gcc -o beep.o beep.c -mmcu=atmega328p -DF_CPU=16000000UL
* avr-objcopy -O ihex beep.o beep.hex
* avrdude -p m328p -P /dev/ttyUSB0 -c arduino -b 19200 -F -u -U flash:w:beep.hex
*
* Connections:
* AREF:	Analog reference
* PB6:	PWM audio
* PC0:	analog control 1
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART_puts.h"
#include "ADC_read.h"
#include "TIMER_beat.h"
#include "context.h"

int main (void) {
	setup_UART_puts();
	setup_ADC();
	volatile context ctx = {0, 10, 0, 0};
	setup_bytebeat(&ctx);
	UART_puts("Everything is set up: UART, ADC, TIMER and bytebeat context.\n\r");
	sei();

	while(1){
		ctx.analog_1 = ADC_read(0);
		//UART_put_hex(ADC_read(0));
		//UART_puts("\n\r");
		//_delay_ms(100);
	}
	return 0;
}
