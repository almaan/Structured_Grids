#include <iostream>

void make_grid(int m, int n){

	double * x_;
	double * y_;

	int m_ = m;
	int n_ = n;

	int n_points = m_*n_;

	std::cout << "Number of points > " << n_points << std::endl;

	x_ = new double [n_points];
	y_ = new double [n_points];

	for (int ii = 0; ii < n_; ii++){
		for (int jj = 0; jj < m_; jj++){
			x_[ii*m_ + jj] = jj;
			y_[ii*m_ + jj] = ii;
		}
	}

	for (int ii = 0; ii < n_points; ii++){
		std::cout << "( " << x_[ii] << "," << y_[ii] << " )" << std::endl;
	}


}

int main(){

	make_grid(4,3);

	return 0;
}