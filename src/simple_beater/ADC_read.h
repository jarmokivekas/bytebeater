#ifndef ADC_read_h
#define ADC_read_h

#include <avr/io.h>
#include <util/delay.h>

void setup_ADC();
uint8_t ADC_read(uint8_t ADCn);

#endif /*ADC_read_h*/
