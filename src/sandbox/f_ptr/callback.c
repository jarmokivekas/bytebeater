#include "callback.h"

//callback global data
uint8_t callback_arg;
void (*callback)(uint8_t);
ISR(INT0_vect){
	callback(callback_arg);
}

void set_callback(void (*ptr)(uint8_t), uint8_t arg){
	callback = ptr;
	callback_arg = arg;
}

/*void exe_callback(){
	callback(callback_arg);
}*/
