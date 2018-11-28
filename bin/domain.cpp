#include <iostream>
#include <cstdio>

#include "domain.h"

Domain::Domain(){};

Domain::~Domain(){};

Domain::Domain(const Domain &d) {
	for (int ii = 0; ii <=3; ii++) {
		sides[ii] = d.sides[ii];
	} 
	x_ = d.x_;
	y_ = d.y_;

	m_ = d.m_;
	n_ = d.n_;
	n_points = d.n_points;
};

Domain & Domain::operator=(const Domain &d) {
	if (this == &d) {
		return *this;
	} else {

		for (int ii = 0; ii <=3; ii++) {
			sides[ii] = d.sides[ii];
		} 
		x_ = d.x_;
		y_ = d.y_;

		m_ = d.m_;	
		n_ = d.n_;
		n_points = d.n_points;	
	}

	return *this;

}


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
	for (int ii = 0; ii < n_points; ii++)
		{
   		 std::cout << x_[ii] << "," << y_[ii] << std::endl;
		} 
}

void Domain::saveCoordinates(bool user_input = false) {
	std::string outname;

	if (user_input){
			std::cout << "Enter name to save file to >> ";
			std::cin >> outname;
	} else {
		outname = "generated_grid.bin";
	}

	std::string x_outname = "../res/x_vec_" + outname;
	std::string y_outname = "../res/y_vec_" + outname;

	FILE *fp_x;
	fp_x =fopen(x_outname.c_str(),"wb");
	fwrite(x_,sizeof(double),m_*n_,fp_x);
	fclose(fp_x);

	FILE *fp_y;
	fp_y =fopen(y_outname.c_str(),"wb");
	fwrite(y_,sizeof(double),m_*n_,fp_y);
	fclose(fp_y);

}