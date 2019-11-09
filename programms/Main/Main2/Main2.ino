#include <SRC16_Rover.h>
#include <Coordinate.h>

#define IWAYOKE 0.7
#define searchBall 1
#define GPSdir 1
#define IWANOMAE 0.5

#define IWAYOKE_TURN_TIME 1300
#define IWAYOKE_STRAIGHT_TIME 3000

#define KP 40

Coordinate now;
Coordinate target;

double north=0.0;

const uint8_t ball[2]={12,13};
int ball_val[2]={};

int power=255;

double distance=0.0;
double direction=0.0;

double start_dir=0.0;
double now_dir=0.0;
int dir_power=0;


void iwayoke(void);
void goToBallGPS(void);
void gotoBall(void);

void setup(void){
	rover.init();
	target.set(135.88755798339843750000,	35.00449752807617187500	);
	rover.motor(FREE,FREE);
	rover.GPSdelay(5000);
}

void loop(void){
	while(!rover.getSW(0)){
		if(rover.getSW(1)){
			north=rover.getBNO(0.0);
			while(rover.getSW(1));
		}
		rover.GPSdelay(50);
	}
	while(rover.getSW(0));

	Serial.println("start");
	now_dir=rover.getBNO(north);

	//iwayoke();
	goToBallGPS();
	if(rover.getSW(1)){
		return;
	}

	/*
	rover.motor(0,0);
	rover.GPSdelay(500);
	*/
	rover.motor(FREE,FREE);
	rover.flag(true);
	rover.GPSdelay(2000);
	rover.flag(false);

	gotoBall();
	if(rover.getSW(1)){
		return;
	}

	rover.motor(FREE,FREE);
	rover.flag(true);
	while(1);
}

void iwayoke(void){
	unsigned long start_time=0;
	Serial.println("iwa");
	while(1){
		start_time=millis();
		while(rover.getHCSR04()>60.0){
			if((millis()-start_time)>2000){
				return;
			}
			rover.motor(power*IWAYOKE,power*IWAYOKE);
		}
		rover.motor(-power*IWAYOKE,-power*IWAYOKE);
		rover.GPSdelay(500);
		rover.motor(power*IWAYOKE,-power*IWAYOKE);
		rover.GPSdelay(IWAYOKE_TURN_TIME);
		rover.motor(power*IWAYOKE,power*IWAYOKE);
		rover.GPSdelay(IWAYOKE_STRAIGHT_TIME);
		rover.motor(-power*IWAYOKE,power*IWAYOKE);
		rover.GPSdelay(IWAYOKE_TURN_TIME);
	}
}

void goToBallGPS(void){
	int count=0;
	bool iwaFlag=true;
	Serial.println("gps");
	while(!rover.getSW(1)){
		rover.GPSdelay(1000);

		now.set(rover.lng(),rover.lat());
		distance=GPShypotenuse(target,now);
		direction=GPStheta(target,now);

		if(iwaFlag){
			if(rover.getHCSR04()<60.0){
				iwaFlag=false;
				rover.motor(0,0);
				iwayoke();
			}
		}

		if(distance<=4.0){
			return;
		}

		do{
			Serial.println("loop");
			now_dir=rover.getBNO(north);
			dir_power=((int)(now_dir+360-direction))%360;
			if(dir_power>180){
				dir_power=dir_power-360;
			}
			dir_power=constrain(dir_power*KP,-255,255);
			rover.motor(-dir_power,dir_power);
			rover.GPSdelay(50);
			if(iwaFlag){
				if(rover.getHCSR04()<30.0){
					iwaFlag=false;
					rover.motor(0,0);
					iwayoke();
				}
			}
		}while(abs(direction-now_dir)>10);


		if(iwaFlag){
			rover.motor(power*IWANOMAE,power*IWANOMAE);
		}else{
			rover.motor(power,power);
		}
		Serial.print(now.x,20);
		Serial.print("\t");
		Serial.print(now.y,20);
		Serial.print("\t");
		Serial.print(distance,10);
		Serial.print("\t");
		Serial.println(direction,20);
	}
	return;
}

void gotoBall(void){
	bool flag=true;
	unsigned long start_time=0;
	Serial.println("ball");
	while(!rover.getSW(1)){
		for(int i=0;i<2;i++){
			ball_val[i]=rover.getAnalog(ball[i]);
			Serial.print(ball_val[i]);
			Serial.print("\t");
		}
		Serial.println("");

		if(ball_val[0]>300){
			if(ball_val[1]>300){
				rover.motor(power,power);
				if(flag){
					flag=false;
					start_time=millis();
				}
				if((millis()-start_time)>1000 && rover.getHCSR04()<15.0){
					return;
				}
			}else{
				rover.motor(-power*searchBall,power*searchBall);
			}
		}else{
			if(ball_val[1]>300){
				rover.motor(power*searchBall,-power*searchBall);
			}else{
				rover.motor(-power*searchBall*0.7,power*searchBall*0.7);
			}
		}
	}
	rover.motor(0,0);
	return;
}
