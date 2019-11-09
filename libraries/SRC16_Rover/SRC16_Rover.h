/*
	SRC16 Real Roverのライブラリ
	2019/10/12から作成
	Perfect-A 工樂瑛友
*/

#ifndef _SRC_ROVER_
#define _SRC_ROVER_

#include <Arduino.h>
#include <Servo.h>
#include <TinyGPS++.h>
#include <Adafruit_BNO055.h>

#define FREE 500

class Rover{
public:
	Rover(void);
	bool init(void);

	//Motor
	void motor(int l,int r);
	void flag(bool val);

	//GPS
	void GPSdelay(unsigned long ms);
	void GPSserial(void);

	uint16_t year(void);
	uint8_t month(void);
	uint8_t day(void);

	uint8_t hour(void);
	uint8_t minute(void);
	uint8_t second(void);
	uint8_t japanHour(void);

	double lat(void);
	double lng(void);
	double alt(void);

	uint32_t sat(void);

	//BNO055
	double getBNO(double n);

	//LED
	void led3(bool a,bool b,bool c);
	void led(uint8_t num,bool val);

	//BUTTON
	bool getSW(uint8_t num);

	//analog
	int getAnalog(uint8_t num);

	//hcsr04
	double getHCSR04(void);

private:
	Servo _flag;
	TinyGPSPlus _tiny;
	Adafruit_BNO055 _bno=Adafruit_BNO055(55);
	sensors_event_t _event;
	const uint8_t _servo_pin=44;
	const uint8_t _motor_pin[2][3]={
		{4,2,9},
		{8,7,10}
	};
	const uint8_t _led_pin[3]={31,33,35};
	const uint8_t _sw_pin[2]={41,37};
	const uint8_t _hcsr04_trig=A9;
	const uint8_t _hcsr04_echo=A10;
	double _hcsr04_val=0;
	unsigned long _start_time=0;
	double _dir=0.0;
};

extern Rover rover;

#endif
