#include "Strongin.h"
#include <math.h>

double Strongin::findConst(std::vector<infoPoint>& points, double  r) {
	double M = 0, maxM = 0, m = 0;
	for (int i = 0; i < points.size() - 1; i++) {
		M = abs((points[i + 1].z - points[i].z) / (points[i + 1].x - points[i].x));
		if (M > maxM)
			maxM = M;
	}
	if (maxM > 0)
		m = r * maxM;
	else if (maxM == 0)
		m = 1;
	return m;
}
int Strongin::findR(std::vector<infoPoint>& points, double  r)
{
	double max = 0;//
	int number = 0;
	double m = findConst(points, r);
	for (int i = 0; i < points.size() - 1; i++)
	{
		double tmp = m * (points[i + 1].x - points[i].x) + pow(points[i + 1].z - points[i].z, 2) / (m* (points[i + 1].x - points[i].x)) - 2.0*(points[i + 1].z + points[i].z);
		if (tmp > max)
		{
			max = tmp;
			number = i;
		}
	}
	return number;
}

double Strongin::getX(std::vector<infoPoint>& points, int& number, double  r)
{
	double m = findConst(points, r);
	return 0.5*(points[number].x + points[number + 1].x) - (points[number + 1].z - points[number].z) / (2.0*m);
}