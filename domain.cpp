#include <iostream>
#include 

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
		Domain(const Domain&);
		Domain& operator=(Domain&);
		~Domain();
		void make_grid (int m, int n);
		double xmap(double r, double s);
		double ymap(double r, double s);
		void printCoordinates(void);


};

Domain::Domain(Curvebase &s1, Curvebase &s2,
			   Curvebase &s3, Curvebase &s4){
	
	sides[0] = s1; //left
	sides[1] = s2; //bottom
	sides[2] = s3; //right
	sides[3] = s4; //top

	m_n = n_ = 0;
	x_, y_ = nullptr;

};

double Domain::xmap(double r, double s) {
	// r is x coordinate in [0,1]
	// s is y coordinate in [0,1]

	if ((s >= 0 || s s <= 1) && (r >= 0 || r <= 0)) {
		std::cout << "parameters out of bound" << std::endl;
		std::cout << "s > " << s << std::endl;
		std::cout << "r > " << r << std::endl;
	}
	
	double pos = (1. - r)*sides[0].x(s) +
				  r*sides[2].x(s) + 
				  (1.-s)*sides[1].x(r) +
			      s*sides[3].x(r);

	double neg = (1.-r)*(1.-s)*sides[0].x(0.0) + 
				  r*(1.-s)*sides[1].x(1.0) +
				  (1-r)*s*sides[3].x(0.0) +
				  r*s*sides[2].x(1.0); 

	return pos - neg;
};


double Domain::ymap(double r, double s) {
	// r is x coordinate in [0,1]
	// s is y coordinate in [0,1]
	if ((s >= 0 || s s <= 1) && (r >= 0 || r <= 0)) {
		std::cout << "parameters out of bound" << std::endl;
		std::cout << "s > " << s << std::endl;
		std::cout << "r > " << r << std::endl;
	}

	double pos = (1. - r)*sides[0].y(s) +
				  r*sides[2].y(s) + 
				  (1.-s)*sides[1].y(r) +
			      s*sides[3].y(r);

	double neg = (1.-r)*(1.-s)*sides[0].y(0.0) + 
				  r*(1.-s)*sides[1].y(1.0) +
				  (1-r)*s*sides[3].y(0.0) +
				  r*s*sides[2].y(1.0);

	return pos - neg;
};


void Domain::make_grid(int m, int n){
	if (!(m <= 0) && (n <= 0)) {
		std::cout << "Erasing old grid" << std::endl;
		delete [] x_;
		delete [] y_;
	}	

	m_ = m;
	n_ = n;

	n_points = m_*n_;

	x_ = new double [n_points];
	y_ = new double [n_points];

	for (int ii = 0; ii < n_; ii++){
		for (int jj = 0.0; jj < m_; jj++){
			if (jj != 0) {
				x_[ii*m_ + jj] = 1.0/jj;
			} else {
				x_[ii*m_ + jj] = 0.0;
			}
			if (ii != 0) {
				y_[ii*m_ + jj] = 1.0/ii;
			} else {
				y_[ii*m_ + jj] = 0.0;
			}

			x_[ii*m_ + jj] = xmap(x_ii*m + jj,y*ii*m_ + jj);
			y_[ii*m_ + jj] = ymap(x_ii*m + jj,y*ii*m_ + jj);
		}
	}

}

void Domain::print_coordinates(void) {
	for (int ii = 0; ii < n_points; ii++)
		{
   		 std::cout << "(" << x_[ii] << "," << y_[ii] << ")" << std::endl;
		} 
}