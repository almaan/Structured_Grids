#ifndef _HLINE
#define _HLINE

#include "curvebase.h"

class Horzline : public Curvebase {
	protected:
		double xp(double p);
		double yp(double p);
		double dxp(double p);
		double dyp(double p);
		virtual double yfunc(double p) = 0;
		virtual double yfuncd(double p) = 0;
	public:
		Horzline(double a, double b) : Curvebase(a,b) {};
		Horzline();
		~Horzline();
};
#endif