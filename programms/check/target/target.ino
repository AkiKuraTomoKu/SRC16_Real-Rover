#include <SRC16_Rover.h>
#include <Coordinate.h>

Coordinate now,target;
double distance=0.0,angle=0.0;

void setup(void){
	rover.init();
	target.set(135.887452,35.004943);
	delay(1000);
}

void loop(void){
	rover.GPSdelay(1000);
	now.set(rover.lng(),rover.lat());
	distance=GPShypotenuse(now,target);
	angle=GPStheta(now,target);

	Serial.print(now.x,10);
	Serial.print("\t");
	Serial.print(now.y,10);
	Serial.print("\t");
	Serial.print(distance,10);
	Serial.print("\t");
	Serial.println(angle,10);
}
