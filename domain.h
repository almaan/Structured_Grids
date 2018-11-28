#ifndef _DOMAIN
#define _DOMAIN

#include "curvebase.h"

class Domain {
	private:
		Curvebase *sides[4];
		double *x_, *y_;
		int m_, n_;
		int n_points;

		double xmap(double r, double s);
		double ymap(double r, double s);

	public:
		Domain();
		Domain(Curvebase &s1, Curvebase &s2,
			   Curvebase &s3, Curvebase &s4);
		Domain(const Domain &d);
		Domain& operator=(const Domain &d);
		~Domain();
		void make_grid (int m, int n);

		void printCoordinates(void);
		void saveCoordinates(bool user_input);

};
#endif