#include <SRC16_Rover.h>

void setup(void){
	rover.init();
}

void loop(void){
	for(int i=0;i<2;i++){
		Serial.print(rover.getSW(i));
		Serial.print("\t");
	}
	Serial.println("");
}
