#include <SRC16_Rover.h>

void setup(void){
	rover.init();
}

void loop(void){
	Serial.println(rover.getBNO(0.0));
	delay(100);
}
