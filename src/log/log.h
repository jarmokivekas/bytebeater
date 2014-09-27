#ifndef log_h
#define log_h

enum log_type{
	ERROR=1,
	WARNING,
	INFO,
};

void setup_print();
void print(int type, char* S);

#endif /*log_h*/
