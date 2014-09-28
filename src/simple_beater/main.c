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

const uint16_t tones[13] = {
	0x8e0b,	//A
	0x8612,	//A#
	0x7e8c,	//B
	0x7772, //C
	0x70bd,	//C#
	0x6a69,	//D
	0x6470,	//D#
	0x5ecd,	//E
	0x597b,	//F
	0x5475,	//F#
	0x4fb8,	//G
	0x4b3e,	//G#
	0x4705	//A
};

int main (void) {
	setup_UART_puts();
	//setup_ADC();
	setup_TIMER0_PWM();
	setup_TIMER1_CTC();
	//volatile context ctx = {0, 0};
	//UART_puts("Everything is set up: UART, ADC, TIMER and bytebeat context.\n\r");
	sei();

	uint8_t i = 0;
	while(1){
		//set samplerate by setting sample length.
		//Most bytebeat tones are multiples of the nyquist frequency
		//so this will define the tone
		OCR1AH = (tones[i]>>8) & 0xff; 
		OCR1AL =  tones[i]     & 0xff; 
		if(++i>12) i=0;
		_delay_ms(100);
	}
	return 0;
}
