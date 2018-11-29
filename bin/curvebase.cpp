#include <iostream>
#include <cmath>
#include "curvebase.h"


//constructor 
Curvebase::Curvebase(double p_min,
					 double p_max,
					 bool dir,
					 double tolerance) {

	pmin = p_min;
	pmax = p_max;
	mid = (p_min + p_max) / 2.0;
	rev = dir;
	tol = tolerance;;
};

void Curvebase::setLength(void){
	length = abs(integrate(pmax,pmin));
}

//default constructor
Curvebase::Curvebase(){};

//default destructor
Curvebase::~Curvebase(){};

//copy constructor
Curvebase::Curvebase(const Curvebase &cb) {
	pmin = cb.pmin;
	pmax = cb.pmax;
	mid = cb.mid;
	rev = cb.rev;
	tol = cb.tol;
};


//Simpson Adaptive Integration
double Curvebase::integrate(double p, double lower){

	double errest = tol + 1.0;
	double integral1, integral2;

	
	integral1 = I1(lower,p);
	integral2 = I2(lower,p);

	//estimate error in approximation
	errest = abs(integral1 - integral2);  

	//refine interval until error below threshold
	if (errest < 15.0*tol) {
		return integral2;
	} else {
		return (integrate((pmin+p)*0.5, pmin) + integrate(p,(pmin+p)*0.5));
	}

};

//helper function for integrate function
double Curvebase::I1(double a_in, double b_in){
		return ((b_in -a_in)/6.0)*(function(a_in)+4*function(0.5*(a_in + b_in)) + function(b_in));
}

//helper function for integrate function
double Curvebase::I2(double a_in, double b_in) {
	double c = (a_in + b_in) * 0.5;
	return I1(a_in,c) + I1(c, b_in);
};

//integrand of integral in curve length computation
//used by integrate function in the adaptive integration
double Curvebase::function(double p) {
	return sqrt( pow(dxp(p),2) + pow(dyp(p),2));
};



//returns x-coordinate of relative position along curve
//relative position is given in interval [0,1]
double Curvebase::x(double s){
	if ( abs(s) > 1.0) {
		std::cout << "ERROR: bad relative position of x-coordinate" << std::endl;
	}
	//get actual length to relative position
	double p = solve(s);
	//get actual x-coordinate for relative position 
	return xp(p);
};

//returns y-coordinate of relative position along curve
//relative position is given in interval [0,1]
double Curvebase::y(double s){
	if ( abs(s) > 1.0) {
		std::cout << "ERROR: bad relative position of x-coordinate" << std::endl;
	}
	//get actual length to relative position
	double p = solve(s);
	//get actual y-coordinate for relative position 
	return yp(p);

};

//Newton Rhapson's method to find actual length
//corresponding to relative position
double Curvebase::solve(double s) {
	
	//set initial guess to length of
	//line segment between endpoints
	double p = s*(pmax - pmin); 
	double p_new;
	double eps = 1e-10;
	double lower;

	int n_iter = 0;
	const int maxiter = 100;

	//iterate untill error is below tolerance or
	//100 iterations have been performed
	do {
		p = p_new;
		if (function(p) == 0.0) {
			std::cout << "Zero Division. Bad Value." << std::endl;
			p_new = p + eps;
		} else {
			//p_new = p - (integrate(p,pmin) - s*length) / function(p);
			p_new = p - (abs(integrate(p,pmin)) - s*length) / function(p);
			
		}
		++n_iter;
	} while ((abs(p-p_new) > tol) && n_iter <= maxiter);

	if (n_iter >= maxiter) {
		std::cout << "ERROR: Convergence not reached." << std::endl;
	}
	return p_new;
};

//reverse orientation of curve
void Curvebase::reverse_orientation(void){
	rev = !rev;
};

bool Curvebase::ori(void){
	return rev;
}

//prints information about curve
//for inquiry of configuration
void Curvebase::printInfo(void){
	std::cout << "lower boundary : > " << pmin << std::endl;
	std::cout << "upper boundary : > " << pmax << std::endl;
	std::cout << "total length : > " << length << std::endl;
	std::cout << "orientation : > " << rev << std::endl;
	std::cout << "x(0.5) : > " << x(0.5) << std::endl;
	std::cout << "y(0.5) : > " << y(0.5) << std::endl;
	return;
};