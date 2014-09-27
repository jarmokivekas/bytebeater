#include "interpreter_test.h"

int interpreter_test(){
	int result = 0;
	result += token_test();
	result += evaluation_test();

	if(result != 0){
		printf("Interpreter:  %d tests FAILED\n", result);
	} else {
		printf("Interpreter:  All tests PASSED\n");
	}
	return result;
}

int token_test(){
	//this function will test that the different tokens are parsed correctly
	//and that their respective functions have the expected effect
	int ret = 0;
	int value;
	
	int input_size = 6;
	beat_context eval_input[] = {
		{"5 3 +", 0},
		{"5 3 -", 0},
		{"5 3 &", 0},
		{"5 3 |", 0},
		{"5 3 ^", 0},
		{"5 3 <<", 0},
	};
	
	int eval_result[] = {
		5 + 3,
		5 - 3,
		5 & 3,
		5 | 3,
		5 ^ 3,
		5 << 3,
	};

	int i;
	for(i=0; i<input_size; i++){
		value = evaluate(&eval_input[i]);
		if(value != eval_result[i]){
			printf("FAIL: interpreter.c:evaluate: evaluation of expression \"%s\" was %d, should be %d.\n",
				eval_input[i].expression,
				value,
				eval_result[i]);
			ret++;
		}
	}
	return ret;
}

int evaluation_test(){
	int ret = 0;
	int value;
	int input_size = 2;
	//try to break something!
	beat_context eval_input[] = {
		{"2A 14 + 9 - 45 ^", 0},
		{"DEAD BAD BEEF + +", 0},
		{"1 1 1 1 1 1 1 1   1 1 1 1 1 1 1 1  + + + + + + + +   + + + + + + + +", 0},
	};
	
	int eval_result[] = {
		((0x2A + 0x14) - 0x9) ^ 0x45,
		0xDEAD + 0xBAD + 0xBEEF,
		16,
	};

	int i;
	for(i=0; i<input_size; i++){
		value = evaluate(&eval_input[i]);
		if(value != eval_result[i]){
			printf("FAIL: interpreter.c:evaluate: evaluation of expression \"%s\" was %d, should be %d.\n",
				eval_input[i].expression,
				value,
				eval_result[i]);
			ret++;
		}
	}
	return ret;
}
