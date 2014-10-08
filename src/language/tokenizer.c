#include "tokenizer.h"

//-------- the defenition of the language --------
const token number = {"number", NULL};
const token error = {"ERROR", NULL};

#define LANG_TOKEN_COUNT 7
const token lang_token[LANG_TOKEN_COUNT] = {
	//keeping the shorter and more often used tokens
	//on the top will make interpreting faster.
	{"+", &add},			//addition
	{"-", &sub},			//subtraction
	{"&", &and_},			//bitwise AND
	{"|", &or_},			//bitwise OR
	{"^", &xor_},			//bitwise XOR
	{"<<", &left_shift},	//left shift
	{"$", NULL}
};


//-------- parsing and tokenizing functions --------
//returns the type of the next token pointed by 'S'
token get_token(char* S){
	int i;
	for(i=0; i<LANG_TOKEN_COUNT; i++){
		/* NON save version:
		if(strcmp(S, lang_token[i].name)){
			return lang_token[i];
		}*/
		if(strncmp(S, lang_token[i].name, strlen(lang_token[i].name)) == 0){
			return lang_token[i];
		}
	}
	//if none of the lang_token tokens match, we have a number or a syntax error
	if( (*S >= '0' && *S <= '9') || (*S >= 'A' && *S <='F') ){
		return number;
	} else {
		return error;
	}
}

//returns the longest caps-hex string that can be read form S
int parse_hex(char* S){
	int n = 0;
	int tmp;
	while(1){	
		switch(*S){
			case '0': tmp=0x0; break;
			case '1': tmp=0x1; break;
			case '2': tmp=0x2; break;
			case '3': tmp=0x3; break;
			case '4': tmp=0x4; break;
			case '5': tmp=0x5; break;
			case '6': tmp=0x6; break;
			case '7': tmp=0x7; break;
			case '8': tmp=0x8; break;
			case '9': tmp=0x9; break;
			case 'A': tmp=0xA; break;
			case 'B': tmp=0xB; break;
			case 'C': tmp=0xC; break;
			case 'D': tmp=0xD; break;
			case 'E': tmp=0xE; break;
			case 'F': tmp=0xF; break;
			/*in the case of a non */
			/*hex character, return*/
			default:        return n;
		}
		n <<= 4;
		n += tmp;
		S++;
	}
}
