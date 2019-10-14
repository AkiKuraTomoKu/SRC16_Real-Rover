/*
	SRC16 Real Roverのライブラリ
	2019/10/12から作成
	Perfect-A 工樂瑛友
*/

#include <Arduino.h>
#include <Servo.h>
#include <TinyGPS++.h>
#include <Adafruit_BNO055.h>
#include "SRC16_Rover.h"

Rover::Rover(){

}

bool Rover::init(){
	Serial.begin(115200);
	Serial2.begin(9600);
	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			pinMode(_motor_pin[i][j],OUTPUT);
		}
	}
	motor(0,0);
	for(int i=0;i<3;i++){
		pinMode(_led_pin[i],OUTPUT);
		digitalWrite(_led_pin[i],LOW);
	}
	_flag.attach(_servo_pin);

	if(!_bno.begin()){
		Serial.println(F("ERROR,no BNO055 detected..."));
		//while(true);
	}
	delay(1000);
	_bno.setExtCrystalUse(true);

	return true;
}

void Rover::motor(int l,int r){
	int val[2]={l,r};
	for(int i=0;i<2;i++){
		if(val[i]!=FREE){
			val[i]=constrain(val[i],-255,255);
		}

		if(val[i]==FREE){
			digitalWrite(_motor_pin[i][0],LOW);
			digitalWrite(_motor_pin[i][1],LOW);
		}else if(val[i]>0){
			digitalWrite(_motor_pin[i][0],HIGH);
			digitalWrite(_motor_pin[i][1],LOW);
		}else if(val[i]<0){
			digitalWrite(_motor_pin[i][0],LOW);
			digitalWrite(_motor_pin[i][1],HIGH);
		}else if(val[i]==0){
			digitalWrite(_motor_pin[i][0],HIGH);
			digitalWrite(_motor_pin[i][1],HIGH);
		}
		analogWrite(_motor_pin[i][2],abs(val[i]));
	}
	/*
	Serial.print(l);
	Serial.print(",");
	Serial.println(r);
	*/
}

void Rover::flag(bool val){
	if(val){
		_flag.write(90);
	}else{
		_flag.write(5);
	}
}

void Rover::GPSdelay(unsigned long ms){
	_start_time=millis();
	do{
		while(Serial2.available())
			_tiny.encode(Serial2.read());
	}while((millis()-_start_time)<ms);
}
void Rover::GPSserial(void){
	Serial.print(year());
	Serial.print("/");
	Serial.print(month());
	Serial.print("/");
	Serial.print(day());
	Serial.print(",");
	Serial.print(hour());
	Serial.print(":");
	Serial.print(minute());
	Serial.print(":");
	Serial.print(second());
	Serial.print(",");
	Serial.print(japanHour());
	Serial.print(":");
	Serial.print(minute());
	Serial.print(":");
	Serial.print(second());
	Serial.print(",");
	Serial.print(lat(),10);
	Serial.print(",");
	Serial.print(lng(),10);
	Serial.print(",");
	Serial.print(alt(),10);
	Serial.print(",");
	Serial.print(sat());
	Serial.println("");
}

uint16_t Rover::year(void){
	return _tiny.date.year();
}
uint8_t Rover::month(void){
	return _tiny.date.month();
}
uint8_t Rover::day(void){
	return _tiny.date.day();
}

uint8_t Rover::hour(void){
	return _tiny.time.hour();
}
uint8_t Rover::minute(void){
	return _tiny.time.minute();
}
uint8_t Rover::second(void){
	return _tiny.time.second();
}
uint8_t Rover::japanHour(void){
	return ((_tiny.time.hour()+9)%24);
}

double Rover::lat(void){
	return _tiny.location.lat();
}
double Rover::lng(void){
	return _tiny.location.lng();
}
double Rover::alt(void){
	return _tiny.altitude.meters();
}

uint32_t Rover::sat(void){
	return _tiny.satellites.value();
}

double Rover::getBNO(void){
	_bno.getEvent(&_event);
	return _event.orientation.x;
}

void Rover::led3(bool a,bool b,bool c){
	digitalWrite(_led_pin[0],a);
	digitalWrite(_led_pin[1],b);
	digitalWrite(_led_pin[2],c);
}

void Rover::led(uint8_t num,bool val){
	digitalWrite(_led_pin[num],val);
}
