#pragma once
#include "baseextremummethod.h"
class Piyavsky :
	public BaseExtremumMethod
{
	double findConst(std::vector<infoPoint>& points, double r);
	int findR(std::vector<infoPoint>& points, double r);
	double getX(std::vector<infoPoint>& points, int& number,double r);
};

