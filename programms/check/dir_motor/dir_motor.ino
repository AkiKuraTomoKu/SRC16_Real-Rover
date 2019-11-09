#include <SRC16_Rover.h>

#define KP 40

double start_dir=0.0;
double now_dir=0.0;
int dir_power=0;

double north=0.0;

void setup(void){
	rover.init();
}

void loop(void){
	while(!rover.getSW(0)){
		if(rover.getSW(1)){
			north=rover.getBNO(0.0);
			while(rover.getSW(1));
		}
		rover.GPSdelay(50);
	}
	start_dir=rover.getBNO(north);
	while(1){
		now_dir=rover.getBNO(north);
		dir_power=((int)(now_dir+360-start_dir))%360;
		if(dir_power>180){
			dir_power=dir_power-360;
		}
		dir_power=constrain(dir_power*KP,-255,255);
		rover.motor(-dir_power,dir_power);

		Serial.print(north);
		Serial.print("\t");
		Serial.print(now_dir);
		Serial.print("\t");
		Serial.print(dir_power);
		Serial.println("");

	}
}
