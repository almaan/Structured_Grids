

#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include "hline.h"
#include "vline.h"
#include "domain.h"


class LeftRightBorder : public Vertline {
	private:
		double x_pos;
		double xfunc(double p);
		double xfuncd(double p);
		

	public:
		LeftRightBorder(double a, double b) : Vertline(a,b) {};
		~LeftRightBorder();
		void setXpos(double p);
		void setLength(void);
};

LeftRightBorder::~LeftRightBorder(){};

void LeftRightBorder::setXpos(double p) {
	x_pos = p;
	return;
};

void LeftRightBorder::setLength(void){
	length =  (abs(pmax-pmin));
};

double LeftRightBorder::xfunc(double p){
	return x_pos;
};

double LeftRightBorder::xfuncd(double p){
	return 0;
};



class TopBorder : public Horzline {
	private:
		double y_pos;
		double yfunc(double p);
		double yfuncd(double p);

	public:
		TopBorder(double a, double b) : Horzline(a,b) {};
		~TopBorder();
		void setYpos(double p);
		void setLength(void);
};


TopBorder::~TopBorder(){};

void TopBorder::setYpos(double p){
	y_pos = p;
	return;
};

void TopBorder::setLength(void){
	length = abs(pmax-pmin);
};

double TopBorder::yfunc(double p){
	return y_pos;
};


double TopBorder::yfuncd(double p){
	return 0;
};


class BottomBorder : public Horzline{
	private:
		double yfunc(double p);
		double yfuncd(double p);
	public:
		BottomBorder(double a, double b) : Horzline(a,b) {};
		~BottomBorder();
};

BottomBorder::~BottomBorder(){};

double BottomBorder::yfunc(double p){
	if (p < -3.0) {
		return 0.5*(1.0/(1.0 +exp(-3.0*(p+6))));
	
	} else if ( p >= -3.0){
		return 0.5*(1.0/(1.0 + exp(3*p)));
	
	} else {
		
		std::cout << "Bottom func: Error fetching point > " << p << std::endl;
		return 0;
	}

};

double BottomBorder::yfuncd(double p){
	if (p < -3) {
	
		double nom = exp(-3.0*p - 18.0*p);
		double den = pow(exp(1.0 + exp(-3.0*p - 18.0*p)),2);
	
		return 1.5 * nom / den;
	
	} else if ( p >= -3){
	
		double nom = exp(3.0*p);
		double den = pow((1.0 + exp(3*p)),2);
	
		return -1.5 * nom / den;

	} else {
	
		std::cout << "Bottom funcd: Error fetching point > " << p << std::endl;
		return 0;
	}

};


int main(){

	std::cout << "Task 1-2" << std::endl;
	std::cout << "\n" << "Test of Curvebase class" << std::endl;

	std::cout << "Left Border" << std::endl;
	LeftRightBorder leftb(0.0,3.0);
	leftb.setXpos(-10.0);
	leftb.setLength();
	leftb.printInfo();


	std::cout << "\n";
	std::cout << "Right border" << std::endl;
	LeftRightBorder rightb(0.0,3.0);
	rightb.setXpos(5.0);
	rightb.setLength();
	rightb.printInfo();

	std::cout << "\n" ;
	std::cout << "Bottom Border " << std::endl;
	BottomBorder botb(-10.0, 5.0);
	botb.setLength();
	botb.printInfo();


	std::cout << "\n";
	std::cout << "Top Border" << std::endl;
	TopBorder topb(-10.0, 5.0);
	topb.setYpos(3.0);
	topb.setLength();
	topb.printInfo();

	std::cout << "\n" << std::endl;
	std::cout << "Task 3-4" << std::endl;
	std::cout << "using above defined boundary curves to generate domain Omega" << std::endl;
	Domain omega(leftb, botb, rightb, topb);


	int n_rows = 50;
	int n_cols = 20;

	omega.make_grid(n_rows, n_cols);
	omega.saveCoordinates(false);
	std::cout << "saved x and y coordinates of grid" << std::endl;

	return 0;
}



