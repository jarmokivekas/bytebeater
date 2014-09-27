#ifndef interface_h
#define interface_h

#include "../struct/beat_context.h"

//set up all interface elements and needed hardware, pins, URAT, etc.
int interface_setup(beat_context* ctx);

//read all the interface elements and modify the beat context accordingly
int interface(beat_context* ctx);

#endif /*interface_h*/
