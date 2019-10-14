#include <Servo.h>

Servo flag;

const uint8_t servo_pin=9;
bool serialFlag=false;

void setup(void){
	Serial.begin(115200);
	flag.attach(servo_pin);
}

void loop(void){
	flag.write(5);
	delay(5000);
	flag.write(90);
	delay(5000);
}
