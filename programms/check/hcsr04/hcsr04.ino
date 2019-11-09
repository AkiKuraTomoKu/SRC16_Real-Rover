#include <SRC16_Rover.h>

void setup(void){
	rover.init();
}

void loop(void){
	Serial.println(rover.getHCSR04());
	delay(50);
}
