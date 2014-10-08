#include "interpreter.h"


int evaluate(beat_context* ctx){
	int stack_memory[MAX_STACK];
	stack s = {stack_memory, 0};
	char* cp = ctx->expression;
	token t;
	int n;
	while(1){
		//skip whitespace
		while(*cp == ' ' || *cp == '\n' || *cp == '\t') cp++;
		if(*cp == 0x00) break;

		t = get_token(cp);
		//HARDCODE: the name of the "number" token
		if( strncmp(t.name, "ERROR", 5) == 0){
			//if no token matches the current string, skip the character
			//and continue from the next one
			print(ERROR, "syntax error");
			cp++;
		} else if(t.name[0] == '$'){
			// token is variable
			int * var_addr = &ctx->var_1;
			cp += 1;
			var_addr += (*cp - 'a');
			push(&s, *var_addr);
			cp += 1;
		} else if( strncmp(t.name, "number", 6) == 0 ){
			n = parse_hex(cp);
			push(&s, n);
			//"remove" the number token from the input string
			while( (*cp >= '0' && *cp <= '9') || (*cp >= 'A' && *cp <='F') ){
				cp++;
			}
		} else {
			t.directive(&s);
			//"remove" the token from the input string
			cp += strlen(t.name);
		}
	}
	return pop(&s);
}
