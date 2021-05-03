#ifndef CEXTREMUM_H
#define CEXTREMUM_H
#include <vector>
#include <iostream>
#include "cfunction.h"
#include "baseextremummethod.h"
#include <memory>
using namespace std;
typedef BaseExtremumMethod::infoPoint infoPoint;
typedef BaseExtremumMethod::vectorCoordinat vectorCoordinat;
//typedef BaseExtremumMethod::vectorFunction vectorFunction;
class CExtremum
{
    shared_ptr<BaseExtremumMethod> p_method;
	std::vector<std::vector<double>> m_data;
	std::vector<std::vector<double>> x_data;
	/*std::vector<double> x2_data;*/
    std::vector<double> m_res;
	std::vector<double> z_func;
    void storeData(const vectorCoordinat& coord);
    double extremum(CFunction& function, vectorCoordinat& coordinats, vectorCoordinat& coordinatsMin, double epsilon, double r, int mon);
    void saveToFile(); 
	void functionToFile(CFunction& function);
public:
    CExtremum(BaseExtremumMethod* method):p_method(method){}
    vectorCoordinat extremum(CFunction& function, double epsilon, double r, int mon);
	int getNumPoints() {
		return m_res.size();
	}

};

#endif // CEXTREMUM_H
