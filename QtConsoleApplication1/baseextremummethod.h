#ifndef BASEEXTREMUMMETHOD_H
#define BASEEXTREMUMMETHOD_H
#include <vector>
#include <iostream>

using namespace std;

class BaseExtremumMethod
{
public:
    BaseExtremumMethod();
    virtual ~BaseExtremumMethod(){}
    //структура точек
    struct vectorCoordinat {
        std::vector<double> x;//координата точки
        double z;//значение функции в точке
        int dim;//размерность
    };


    struct infoPoint {
        double x;
		double f;
        double z;
		infoPoint(double x = 0, double f = 0, double z = 0) {}
    };
    virtual int findR(std::vector<infoPoint>& points, double r);
    virtual double getX(std::vector<infoPoint>& points, int& number, double r);
};

#endif // BASEEXTREMUMMETHOD_H

int showSize(std::vector<BaseExtremumMethod::infoPoint>& points);
