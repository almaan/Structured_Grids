#include "hline.h"

Horzline::Horzline(){};
Horzline::~Horzline(){};

double Horzline::xp(double p){
	return p;

};

double Horzline::dxp(double p){
	return 1;
};

double Horzline::yp(double p){
	return yfunc(p);
};

double Horzline::dyp(double p) {
	return yfuncd(p);
};