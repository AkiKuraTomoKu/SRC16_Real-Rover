#include <SRC16_Rover.h>

Rover rover;

void setup(void){
	rover.init();
}

void loop(void){
	rover.motor(255,255);
	delay(1000);
	rover.motor(0,0);
	delay(2000);
	rover.motor(-255,-255);
	delay(1000);
	rover.motor(FREE,FREE);
	delay(2000);
}
