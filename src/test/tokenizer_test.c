#include "tokenizer_test.h"

int tokenizer_test(){
	int result = 0;
	result += get_token_test();
	result += parse_hex_test();	
	if(result != 0){
		printf("Tokenizer:    %d tests FAILED\n", result);
	} else {
		printf("Tokenizer:    All tests PASSED\n");
	}
	return result;
}

int get_token_test(){
	char* S;
	token T;;
	int ret = 0;
	
	S = "+";
	T = get_token(S);
	if(strncmp(T.name, "+", 1) != 0){
		puts("FAIL: tokenizer.c:get_token: \"+\" was parsed wrong\n");
		ret++;
	}

	S = "-";
	T = get_token(S);
	if(strncmp(T.name, "-", 1) != 0){
		puts("FAIL: tokenizer.c:get_token: \"-\" was parsed wrong\n");
		ret++;
	}

	S = "2A";
	T = get_token(S);
	if(strncmp(T.name, "number", 6) != 0){
		puts("FAIL: tokenizer.c:get_token: \"2A\" was parsed wrong\n");
		ret++;
	}
	return ret;
}

int parse_hex_test(){
	int ret = 0;
	int value;

	//regular hex
	value = parse_hex("2AF5");
	if(value != 0x2AF5){
		puts("FAIL: tokenizer.c:parse_hex: token \"2AF5\" was parsed wrong");
		ret++;
	}
	//using non-caps as hex
	value = parse_hex("2af5");
	if(value != 0x2){
		puts("FAIL: tokenizer.c:parse_hex: token \"2a\" was parsed wrong");
		ret++;
	}
	//hex followed by other tokens/trash
	value = parse_hex("2Atrash");
	if(value != 0x2A){
		puts("FAIL: tokenizer.c:parse_hex: token \"2Atrash\" was parsed wrong");
		ret++;
	}
	//followed by non-alphanumerics
	value = parse_hex("2A+-!");
	if(value != 0x2A){
		puts("FAIL: tokenizer.c:parse_hex: token \"2A+-!\" was parsed wrong");
		ret++;
	}
	//preceded by trash
	value = parse_hex("trash2A");
	if(value != 0x00){
		puts("FAIL: tokenizer.c:parse_hex: token \"trash2A\" was parsed wrong");
		ret++;
	}
	//too long for integer, begginning is cut
	value = parse_hex("2A1876BCD123");
	if(value != 0x76BCD123){
		puts("FAIL: tokenizer.c:parse_hex: token \"2A1876BCD123\" was parsed wrong");
		ret++;
	}

	return ret;
}
