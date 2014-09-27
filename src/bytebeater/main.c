#include "main.h"

int main(){
	beat_context ctx;
	interface_setup(&ctx);
	timer_setup(&ctx);
	while(1){
		interface(&ctx);
	}
	return 0;
}
