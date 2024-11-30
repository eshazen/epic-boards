#include <math.h>

//
// From https://gist.github.com/rzhukov
// oddly, r, g, b seem to be in range [0:3]
// h is radians, s, i are [0:1]

#define RGB_MAX 3.0

void HSI2RGB(double h, double s, double i, double* r, double* g, double* b)
{
	double x = i * (1 - s);		
	if(h < 2 * M_PI / 3)
	{
		double y = i * (1 + (s * cos(h)) / (cos(M_PI / 3 - h)));
		double z = 3 * i - (x + y);
		*b = x; *r = y; *g = z;
	}
	else if(h < 4 * M_PI / 3)
	{
		double y = i * (1 + (s * cos(h - 2 * M_PI / 3)) / (cos(M_PI / 3 - (h  - 2 * M_PI / 3))));
		double z = 3 * i - (x + y);
		*r = x; *g = y; *b = z;
	}
	else
	{
		double y = i * (1 + (s * cos(h - 4 * M_PI / 3)) / (cos(M_PI / 3 - (h  - 4 * M_PI / 3))));
		double z = 3 * i - (x + y);
		*r = z; *g = x; *b = y;
	}
}

void RGB2HSI(double r, double g, double b, double* h, double* s, double* i)
{
   	*i = (r + g + b) / 3.0;

	double rn = r / (r + g + b);
	double gn = g / (r + g + b);
	double bn = b / (r + g + b);

	*h = acos((0.5 * ((rn - gn) + (rn - bn))) / (sqrt((rn - gn) * (rn - gn) + (rn - bn) * (gn - bn))));
	if(b > g)
	{
		*h = 2 * M_PI - *h;	
	}

	*s = 1 - 3 * fmin(rn, fmin(gn, bn));
}
