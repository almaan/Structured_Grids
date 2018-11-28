#ifndef _CURVEBASE
#define _CURVEBASE

class Curvebase {

protected:
	double pmin; // minimal value for p
	double pmax; // maximal value for p
	double mid;
	bool rev; // orientation of the curve
	double tol;

	double length;

	virtual double xp(double p) = 0; //original x curve coordinates
	virtual double yp(double p) = 0; //original ycurve coordinates
	virtual double dxp(double p) = 0; //original x curve derivative
	virtual double dyp(double p) = 0; //original y curve derivative

	double function(double p); //function to be integrated
	double integrate(double p, double lower); //arc length integral
	double solve(double s); //newton rhapson fixed point iteration solver
	
	double I1(double a, double b);
	double I2(double a, double b);


public:

	Curvebase(double p_min,
			  double p_max,
			  bool dir = 1,
	 		  double tolerance = 10e-5);

	Curvebase(); //constructor
	~Curvebase(); //destruvtor
	Curvebase(const Curvebase &cb);
	double x(double s); //arc length parametrization
	double y(double s); //arc length parametrization
	virtual void setLength(void);
	void printInfo(void);

};

#endif