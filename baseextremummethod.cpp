#include "baseextremummethod.h"
BaseExtremumMethod::BaseExtremumMethod()
{

}

int BaseExtremumMethod::findR(std::vector<BaseExtremumMethod::infoPoint> &points, double r)
{
    double max = 0;//
        int number = 0;
        for (int i = 0; i < points.size() - 1; i++)
        {
            double tmp = points[i + 1].x - points[i].x;
            if (tmp > max)
            {
                max = tmp;
                number = i;
            }
        }
        return number;
}

double BaseExtremumMethod::getX(std::vector<BaseExtremumMethod::infoPoint> &points, int &number, double r)
{
    return (points[number].x + points[number + 1].x) / 2;
}

int showSize(std::vector<BaseExtremumMethod::infoPoint> &points) {
	return points.size();
}