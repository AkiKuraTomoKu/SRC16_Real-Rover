#include <Coordinate.h>

Coordinate a,b;

void setup(void){
	a.set(0.0,0.0);
	b.set(1.0,1.0);
	Serial.begin(115200);
	Serial.print("hypotenuse:");
	Serial.println(hypotenuse(a,b));
	Serial.print("theta:");
	Serial.println(theta(a,b));
}

void loop(void){}
