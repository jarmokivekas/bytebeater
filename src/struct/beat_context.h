#ifndef beat_context_h
#define beat_context_h

typedef struct beat_context{
	char* expression;	//beatlang expression
	int t;				//first time variable
	int t_v;			//time variable velocity
	int var_1, var_2;	//variables in expression
} beat_context;

#endif /*beat_context_h*/
