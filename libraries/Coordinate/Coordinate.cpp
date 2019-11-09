/*
	座標などのライブラリ
	Perfect-A 工樂瑛友
*/

#include <Arduino.h>
#include "Coordinate.h"

void Coordinate::set(double a,double b){
	x=a;
	y=b;
}

double hypotenuse(Coordinate ab,Coordinate xy){
	return ( sqrt( pow(ab.x-xy.x,2) + pow(ab.y-xy.y,2) ) );
}

double theta(Coordinate ab,Coordinate xy){
	return ( atan2(ab.y-xy.y,ab.x-xy.x)*RAD_TO_DEG );
}

double GPShypotenuse(Coordinate ab,Coordinate xy){
	return ( sqrt( pow((ab.x-xy.x)*JAPAN_ONE_X,2) + pow((ab.y-xy.y)*JAPAN_ONE_Y,2) ) );
	//return ( sqrt( pow((ab.x-xy.x),2) + pow((ab.y-xy.y),2) ) );
}

double GPStheta(Coordinate ab,Coordinate xy){
	double _theta=0.0;
	_theta=atan2((ab.y-xy.y)*JAPAN_ONE_Y,(ab.x-xy.x)*JAPAN_ONE_X)*RAD_TO_DEG;
	_theta=90.0-_theta;
	if(_theta<0.0){
		_theta+=360.0;
	}else if(_theta>=360.0){
		_theta-=360.0;
	}
	return (_theta);
}
