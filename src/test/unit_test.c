#include "unit_test.h"

int main(){
	printf("\n[-------- Unit tests --------]\n");
	int result = 0;

	//run the tests for all the units
	result += interpreter_test();
	result += tokenizer_test();

	if(result != 0){
		printf("Unit testing: %d tests FAILED\n", result);
	} else {
		printf("Unit testing: All tests PASSED\n");
	}
	return 0;
}
