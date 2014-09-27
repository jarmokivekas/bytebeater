#ifndef stack_machine_h
#define stack_machine_h

#include "../log/log.h"

#define MAX_STACK 100
typedef struct stack{
	int* arr;
	int top;
} stack;

void reset(stack* s);
int pop(stack* s);
void push(stack* s, int a);

void add(stack* s);
void sub(stack* s);
void and_(stack* s);		//named and_ because and is reserved
void or_(stack* s);			//named or_ because or is reserved
void xor_(stack* s);		//named xor_ because xor is reserved
void left_shift(stack* s);
#endif /*stack_machine_h*/
