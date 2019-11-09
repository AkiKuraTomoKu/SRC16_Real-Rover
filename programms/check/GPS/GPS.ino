#include <SRC16_Rover.h>

void setup(void){
	rover.init();
}

void loop(void){
	rover.GPSserial();
	rover.GPSdelay(1000);
}
