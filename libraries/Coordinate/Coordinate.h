/*
	座標などのライブラリ
	Perfect-A 工樂瑛友
*/

//LNG X
//LAT Y

#ifndef _COORDINATE_
#define _COORDINATE_

#include <Arduino.h>

#define JAPAN_ONE_X 91497.5034218
#define JAPAN_ONE_Y 110941.2

class Coordinate{
public:
	void set(double a,double b);
	double x=0.0;
	double y=0.0;
};


double hypotenuse(Coordinate xy,Coordinate ab);
double theta(Coordinate xy,Coordinate ab);
double GPShypotenuse(Coordinate xy,Coordinate ab);
double GPStheta(Coordinate xy,Coordinate ab);

#endif //#ifndef _COORDINATE_
