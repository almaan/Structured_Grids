#include "vline.h"

Vertline::Vertline(){};
Vertline::~Vertline(){};

double Vertline::xp(double p){
	return xfunc(p);
};

double Vertline::dxp(double p){
	return xfuncd(p);
};

double Vertline::yp(double p){
	return p;
};

double Vertline::dyp(double p){
	return 1;
};