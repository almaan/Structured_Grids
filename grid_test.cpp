#include <iostream>

void make_grid(int m, int n){

	double * x_;
	double * y_;

	int m_ = m;
	int n_ = n;

	double dx = 1.0/((double)m_-1);
	double dy = 1.0/((double)n_-1);

	std::cout << "dx > " << dx << std::endl;
	std::cout << "dy > " << dy << std::endl;

	int n_points = m_*n_;

	std::cout << "Number of points > " << n_points << std::endl;

	x_ = new double [n_points];
	y_ = new double [n_points];

	int k = 0;

	for (int ii = 0; ii < n_; ii++){
		for (int jj = 0; jj < m_; jj++){
			std::cout << ii*m + jj << std::endl;
			x_[ii*m_ + jj] = dx*(double)jj;
			y_[ii*m_ + jj] = dy*(double)ii;
			k++;
		}
	}
	std::cout << "number of iters > " << k << std::endl;
	for (int ii = 0; ii < n_points; ii++){
		std::cout << "( " << x_[ii] << "," << y_[ii] << " )" << std::endl;
	}


}

int main(){

	make_grid(4,4);

	return 0;
}