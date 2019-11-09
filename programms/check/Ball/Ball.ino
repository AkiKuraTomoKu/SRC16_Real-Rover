#include <SRC16_Rover.h>

const uint8_t ball[2]={12,13};

void setup(void){
	rover.init();
}

void loop(void){
	for(int i=0;i<2;i++){
		Serial.print(rover.getAnalog(ball[i]));
		Serial.print("\t");
	}
	Serial.println("");
}
