#include "stack_machine.h"

//--------regular stack operations
void  reset(stack* s){
	s->top = 0;
}

int pop(stack* s){
	int ret;
	ret = s->arr[s->top];
	s->top--;
	//avoid stack underflow
	if(s->top < 0 ){
		print(ERROR, "stack underflow");
		s->top = 0;
	}
	return ret;
}

void push(stack* s, int a){
	s->top++;
	//avoid stack overflow
	if(s->top > MAX_STACK){
		print(ERROR, "stack underflow");
		s->top = MAX_STACK;
	}
	s->arr[s->top] = a;
}

void add(stack* s){
	int a = pop(s);
	int b = pop(s);
	push(s, a+b);
}

void sub(stack* s){
	int a = pop(s);
	int b = pop(s);
	push(s, b-a);
}

void and_(stack* s){
	int a = pop(s);
	int b = pop(s);
	push(s, b&a);
}

void or_(stack* s){
	int a = pop(s);
	int b = pop(s);
	push(s, b|a);
}

void xor_(stack* s){
	int a = pop(s);
	int b = pop(s);
	push(s, b^a);
}

void left_shift(stack* s){
	int a = pop(s);
	int b = pop(s);
	push(s, b << a);
}
