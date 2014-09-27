#ifndef interpreter_h
#define interpreter_h

#include "../log/log.h"

#include <string.h>
#include "stack_machine.h"
#include "tokenizer.h"
#include "../struct/beat_context.h"

int evaluate(beat_context* ctx);

#endif /*interpreter_h*/
