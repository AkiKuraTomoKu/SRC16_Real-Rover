#include <SRC16_Rover.h>

double north=0.0;

void setup(void){
	rover.init();
}

void loop(void){
	if(rover.getSW(1)){
		north=rover.getBNO(0.0);
		while(rover.getSW(1));
	}
	Serial.println(rover.getBNO(north));
	delay(100);
}
