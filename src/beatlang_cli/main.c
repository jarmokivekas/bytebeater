/*
Juha Kivekäs
21.9.2014

This is a commandline interface for using the beatlang interpreter.
The main purpose of this utility is testing the interpreter and language.
*/

#include "main.h"

const char* help =
	"/*here i should write something helpful*/";

int main(){
	char input[100];
	beat_context ctx;
	ctx.expression = input;
	ctx.var_1 = 10;
	ctx.var_2 = 64;
	while(1){
		fgets(input, 100, stdin);
		if( strncmp(input, "quit", 4) == 0 ) return 0;
		if( strncmp(input, "help", 4) == 0 ) puts(help);
		else {
			printf("0x%X\n", evaluate(&ctx));
		}	
	}
}
