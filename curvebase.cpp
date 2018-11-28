#include <iostream>
#include <cmath>
#include "curvebase.h"

Curvebase::Curvebase(double p_min,
					 double p_max,
					 bool dir,
					 double tolerance) {

	pmin = p_min;
	pmax = p_max;
	mid = (p_min + p_max) / 2.0;
	rev = dir;
	tol = tolerance;
	//setLength();
};

void Curvebase::setLength(void){
	//TODO : implment rotation option here
	length = abs(integrate(pmax,pmin));
}

Curvebase::Curvebase(){};

Curvebase::~Curvebase(){};

Curvebase::Curvebase(const Curvebase &cb) {
	pmin = cb.pmin;
	pmax = cb.pmax;
	mid = cb.mid;
	rev = cb.rev;
	tol = cb.tol;
};

void Curvebase::printInfo(void){
	std::cout << "lower boundary : > " << pmin << std::endl;
	std::cout << "upper boundary : > " << pmax << std::endl;
	std::cout << "total length : > " << length << std::endl;
	std::cout << "x(0.5) : > " << x(0.5) << std::endl;
	std::cout << "y(0.5) : > " << y(0.5) << std::endl;
	return;
};

//Simpson Adaptive Integration
double Curvebase::integrate(double p, double lower){

	double errest = tol + 1.0;
	double integral1, integral2;

	
	integral1 = I1(lower,p);
	integral2 = I2(lower,p);

	errest = abs(integral1 - integral2);  

	if (errest < 15.0*tol) {
		return integral2;
	} else {
		return (integrate((pmin+p)*0.5, pmin) + integrate(p,(pmin+p)*0.5));
	}

};

double Curvebase::I1(double a_in, double b_in){
		return ((b_in -a_in)/6.0)*(function(a_in)+4*function(0.5*(a_in + b_in)) + function(b_in));
}

double Curvebase::I2(double a_in, double b_in) {
	double c = (a_in + b_in) * 0.5;
	return I1(a_in,c) + I1(c, b_in);
};


double Curvebase::function(double p) {
	return sqrt( pow(dxp(p),2) + pow(dyp(p),2));
};


double Curvebase::x(double s){
	//get position on curve w.r.t. to x coordinate
	double p = solve(s);
	//necessary y-transform coordinate
	return xp(p);


};


double Curvebase::y(double s){
	//get position on curve w.r.t. to y coordinate
	double p = solve(s);
	//necessary transformation for y
	return yp(p);

};

double Curvebase::solve(double s) {
	//std::cout << "Solve : s > " <<  s << std::endl;
	double p = (s*pmax + pmin) * 0.5;	
	double p_new = p + 1.0;
	int n_iter = 0;
	const int maxiter = 100;

	while ((abs(p-p_new) > tol) && n_iter <= maxiter) {
		p = p_new;
		if (function(p) == 0.0) {
			std::cout << "Zero Division. Bad Value." << std::endl;
			p_new = p;
		} else {
			p_new = p - (integrate(p,pmin) - s*length) / function(p);
			
		}
		++n_iter;
	}

	if (n_iter >= maxiter) {
		std::cout << "ERROR: Convergence not reached." << std::endl;
	}
	//std::cout << "point appr > s -> "<< s << ":" << p_new << std::endl;
	return p_new;
};