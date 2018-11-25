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
		delete [] y;
	}	

	m_ = m;
	n_ = n;

	x_ = new double [m_*n_];
	y_ = new double [m_*n_];


}