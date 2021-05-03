#include "Piyavsky.h"
#include <math.h>
double Piyavsky :: findConst(std::vector<infoPoint> &points, double  r) {
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


int Piyavsky::findR(std::vector<infoPoint>& points, double  r)
{
	//infoPoint point;
	//std::vector<infoPoint> infoPoints;
	double max;//
	vector <double> characteristic;
	int number = 0;
	double m = findConst(points, r);
	for (int i = 0; i < points.size() - 1; i++)
	{
		double tmp = 0.5*m*(points[i + 1].x - points[i].x) - (points[i + 1].z + points[i].z) / 2.0;
		characteristic.push_back(tmp);
		if(i==0)max = tmp;
		/*if (tmp > max)
		{
			max = tmp;
			number = i;
		}*/
	}
	for (int i = 0; i < characteristic.size() - 1; i++) {
		if (characteristic[i] > max)
		{
			max = characteristic[i];
			number = i;
		}
	}
	characteristic.clear();
	return number;
}

double Piyavsky::getX(std::vector<infoPoint>& points, int& number, double  r)
{
	//infoPoint point;
	//std::vector<infoPoint> infoPoints;
	double m = 1;
	m = findConst(points, r);
	return 0.5*(points[number].x + points[number + 1].x) - (points[number + 1].z - points[number].z) / (2.0*m);
}