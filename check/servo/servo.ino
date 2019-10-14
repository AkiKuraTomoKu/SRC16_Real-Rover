#include <Servo.h>

Servo flag;

const uint8_t servo_pin=9;
bool serialFlag=false;

void setup(void){
	Serial.begin(115200);
	flag.attach(servo_pin);
}

void loop(void){
	if(!serialFlag){
		for(int i=0;i<180;i++){
			flag.write(i);
			Serial.println(i);
			delay(20);
		}
		for(int i=180;i>0;i--){
			flag.write(i);
			Serial.println(i);
			delay(20);
		}
	}
	if(Serial.available()){
		int deg;
		serialFlag=true;
		delay(500);
		deg=Serial.parseInt();
		flag.write(deg);
	}
}
