#ifndef tokenizer_h
#define tokenizer_h

#include <string.h>
#include "./stack_machine.h"	//for the directive functions

typedef struct token{
	char* name;
	void (*directive)(stack*);
} token;

//if the tokenizer returns a t_number token, then the token has to be
//re-parsed as an integer and saved appropriately
token get_token(char* S);

//parses S for the next CPAS hex
int parse_hex(char* S);

#endif /*tokenizer_h*/
