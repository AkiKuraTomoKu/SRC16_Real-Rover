#include <SRC16_Rover.h>

void setup(void){
	rover.init();
}

void loop(void){
	rover.flag(1);
	delay(5000);
	rover.flag(0);
	delay(5000);
}
