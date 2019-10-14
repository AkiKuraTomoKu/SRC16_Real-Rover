#include <SRC16_Rover.h>

Rover rover;

void setup(void){
	rover.init();
}

void loop(void){
	for(int i=0;i<3;i++){
		rover.led(i,1);
		delay(1000);
		rover.led(i,0);
		delay(1000);
	}
	rover.led3(1,1,1);
	delay(1000);
	rover.led3(0,0,0);
	delay(1000);
}
