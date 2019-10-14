#include <SRC16_Rover.h>

Rover rover;

void setup(void){
	rover.init();
}

void loop(void){
	Serial.println(rover.getBNO());
	delay(100);
}
