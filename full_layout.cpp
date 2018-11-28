

#include <iostream>
#include <cmath>
#include "hline.h"
#include "vline.h"


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

class Domain {
	private:
		Curvebase *sides[4];
		double *x_, *y_;
		int m_, n_;
		int n_points;
//		bool check_consistency();

	public:
		Domain(Curvebase &s1, Curvebase &s2,
			   Curvebase &s3, Curvebase &s4);
//		Domain(const Domain&);
//		Domain& operator=(Domain&);
		~Domain();
		void make_grid (int m, int n);
		double xmap(double r, double s);
		double ymap(double r, double s);
		void printCoordinates(void);


};

Domain::~Domain(){};

Domain::Domain(Curvebase &s1, Curvebase &s2,
			   Curvebase &s3, Curvebase &s4){
	
	sides[0] = &s1; //left
	sides[1] = &s2; //bottom
	sides[2] = &s3; //right
	sides[3] = &s4; //top

	m_ = n_ = 0;
	x_, y_ = nullptr;

};

double Domain::xmap(double r, double s) {
	// r is x coordinate in [0,1]
	// s is y coordinate in [0,1]

	double pos = (1. - r)*sides[0]->x(s) +
				  r*sides[2]->x(s) + 
				  (1.-s)*sides[1]->x(r) +
			      s*sides[3]->x(r);

	double neg = (1.-r)*(1.-s)*sides[0]->x(0.0) + 
				  r*(1.-s)*sides[1]->x(1.0) +
				  (1-r)*s*sides[3]->x(0.0) +
				  r*s*sides[2]->x(1.0); 

	return pos - neg;
};


double Domain::ymap(double r, double s) {
	// r is x coordinate in [0,1]
	// s is y coordinate in [0,1]

	if (s < 0 || s > 1 || r < 0 || r > 1) {
		std::cout << "parameters out of bound" << std::endl;
	}

	double pos = (1. - r)*sides[0]->y(s) +
				  r*sides[2]->y(s) + 
				  (1.-s)*sides[1]->y(r) +
			      s*sides[3]->	y(r);

	double neg = (1.-r)*(1.-s)*sides[0]->y(0.0) + 
				  r*(1.-s)*sides[1]->y(1.0) +
				  (1-r)*s*sides[3]->y(0.0) +
				  r*s*sides[2]->y(1.0);

	return pos - neg;
};


void Domain::make_grid(int m, int n){
	if (!(m <= 0) && (n <= 0)) {
		std::cout << "Erasing old grid" << std::endl;
		delete [] x_;
		delete [] y_;
	}	

	int pos;

	m_ = m;
	n_ = n;

	double dx = 1.0/(double(m_) -1.0);
	double dy = 1.0/(double(n_) -1.0);

	n_points = m_*n_;

	x_ = new double [n_points];
	y_ = new double [n_points];

	for (int ii = 0; ii < n_; ii++){
		for (int jj = 0; jj < m_; jj++){

			pos = ii*m_ + jj;

			x_[pos] = xmap(dx*(double)jj, dy*(double)ii);
			y_[pos] = ymap(dx*(double)jj, dy*(double)ii);

		}
	}

}

void Domain::printCoordinates(void) {
	std::cout << "#>" << std::endl;
	for (int ii = 0; ii < n_points; ii++)
		{
   		 std::cout << x_[ii] << "," << y_[ii] << std::endl;
		} 
}


int main(){

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

	std::cout << "\n Domain Information: " << std::endl;

	Domain dmn(leftb, botb, rightb, topb);
	int n_rows, n_cols;
	std::cout << "Enter number of rows > ";
	std::cin >> n_rows;
	std::cout << "Enter number of cols > ";
	std::cin >> n_cols;

	dmn.make_grid(n_rows,n_cols);
	dmn.printCoordinates();

	return 0;
}



