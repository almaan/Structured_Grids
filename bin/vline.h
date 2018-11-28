#ifndef _VLINE
#define _VLINE

#include "curvebase.h"

class Vertline : public Curvebase {
	protected:

		double xp(double p);
		double yp(double p);
		double dxp(double p);
		double dyp(double p);

		virtual double xfunc(double p) = 0;
		virtual double xfuncd(double p) = 0;

	public:
		Vertline(double a, double b) : Curvebase(a,b) {};
		Vertline();
		~Vertline();
};

#endif