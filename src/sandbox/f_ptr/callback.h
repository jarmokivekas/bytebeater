#include <avr/io.h>
#include <avr/interrupt.h>
void set_callback(void (*ptr)(uint8_t), uint8_t arg);
void exe_callback();
