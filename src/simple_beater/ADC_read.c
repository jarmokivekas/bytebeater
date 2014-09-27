#include "ADC_read.h"

void setup_ADC(){
	//AREF will be the reference source
	// Left adjust ADC result to allow easy 8 bit reading
	ADMUX |= (1 << ADLAR);

	// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Enable ADC
	ADCSRA |= (1 << ADEN);
}

uint8_t ADC_read(uint8_t ADCn){
	//select the analog channel
	ADMUX &= ~0x07;			//wipe three lowest bits
	ADMUX |=  0x07 & ADCn; 	//write three lowest bits
	ADCSRA |= (1 << ADSC);	//Start ACD Conversions

	while((ADCSRA & (1<<ADIF)) == 0){
		/*DO NOTHING, wait until conversion is done*/
	}
	ADCSRA |= (1<<ADIF);	//reset interrupt flag
	return ADCH;			//return the ADC value
}
