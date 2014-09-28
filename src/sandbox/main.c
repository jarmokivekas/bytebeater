#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER1_COMPA_vect){
	PORTB ^= (1<<DDB0);
}

void setup_TIMER0_CTC(){
	TCCR1B |= /*(1<<CS12)|*/ (1<<CS10);	//1024 prescaler
	TCCR1B |= (1<<WGM12);				//CTC with OCR1A
	TIMSK1 |= (1<<OCIE1A);				//unmask output compare interrupt
	sei();
}

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

const uint8_t tune[3] = {
	3,
	7,
	10
};

int main(){
	setup_TIMER0_CTC();
	DDRB |= (1<<DDB0);
	uint8_t i = 0;
	while(1){
		
		OCR1AH = (tones[tune[i]]>>8) & 0xff; 
		OCR1AL =  tones[tune[i]]     & 0xff; 
		i++;
		if(i>2) i=0;
		_delay_ms(50);
	}
	return 0;
}
