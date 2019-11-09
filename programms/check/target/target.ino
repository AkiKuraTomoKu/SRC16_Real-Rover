#include <SRC16_Rover.h>
#include <Coordinate.h>

Coordinate now;
Coordinate target;
double distance=0.0,angle=0.0;

void setup(void){
	rover.init();
	target.set(135.88755798339843750000	,35.00452423095703125000		);//center
	// target.set(135.0,35.0);
	delay(1000);
}

void loop(void){
	rover.GPSdelay(1000);
	now.set(rover.lng(),rover.lat());
	distance=GPShypotenuse(target,now);
	angle=GPStheta(target,now);

	Serial.print(now.x,20);
	Serial.print("\t");
	Serial.print(now.y,20);
	Serial.print("\t");
	Serial.print(distance,10);
	Serial.print("\t");
	Serial.println(angle,20);
}
