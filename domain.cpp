class Domain {
	private:
		Curvebase *sides[4];
		double *x_, *y_;
		int m_, n_;
//		bool check_consistency();

	public:
		Domain(Curvebase &s1, Curvebase &s2,
			   Curvebase &s3, Curvebase &s4);
		Domain(const Domain&);
		Domain& operator=(Domain&);
		~Domain();
		void make_grid (int m, int n);
		double return xmap()


};

Domain::Domain(Curvebase &s1, Curvebase &s2,
			   Curvebase &s3, Curvebase &s4){
	
	sides[0] = s1;
	sides[1] = s2;
	sides[2] = s3;
	sides[3] = s4;

	m_n = n_ = 0;
	x_, y_ = nullptr;

};

void Domain::make_grid(int m, int n){
	if (!(m <= 0) && (n <= 0)) {
		std::cout << "Erasing old grid" << std::endl;
		delete [] x_;
		delete [] y_;
	}	

	m_ = m;
	n_ = n;

	int n_points = m_*n_;

	x_ = new double [n_points];
	y_ = new double [n_points];

	for (int ii = 0; ii < n_; ii++){
		for (int jj = 0; jj < m_; jj++){
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
		}
	}

}