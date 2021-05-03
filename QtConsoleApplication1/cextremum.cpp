#include "mainwindow.h"
#include "ui_GlobOpt.h"
#include "cextremum.h"
#include <fstream>
#include <iomanip>
#include <math.h> 
using namespace std;


void CExtremum::storeData(const vectorCoordinat &coord)
{
	unsigned int i = 0;
	for (double x : coord.x)
		m_data.at(i++).push_back(x); // data[0] -x1 data[1] -x2 etc.
	m_res.push_back(coord.z);
}


double CExtremum::extremum(CFunction &function, vectorCoordinat &coordinats, vectorCoordinat &coordinatsMin, double epsilon, double r, int mon)
{
	double currentMin = NULL, currentMax = NULL;
	int count = 0;
	
	if (coordinats.dim < function.GetDimention())
	{
		
		double f_left = NULL, f_right = NULL;
		infoPoint point;
		std::vector<infoPoint> infoPoints;

		point.x = coordinats.x[coordinats.dim] = function.LeftX(coordinats.dim); // левая граница для текущеого coordinats.dim ого пространства
		coordinats.dim++;
		point.f = extremum(function, coordinats, coordinatsMin, epsilon, r, mon);
		if (f_left == NULL)f_left = point.f;
		point.z = point.f;//по умолчанию это одно и тоже
		coordinats.dim--;
		infoPoints.push_back(point); //сохраняем точку и значение экстремума
		point.x = coordinats.x[coordinats.dim] = function.RightX(coordinats.dim);
		coordinats.dim++;
		//отсюда начинается по x1 искать.. нужно подумать как x1-ым присвоить значения минимумов
		//проверить тут, что это именно x1 ищется + не концы, концы сверху определяются
		//

			point.f = extremum(function, coordinats, coordinatsMin, epsilon, r, mon);

		if (f_right == NULL)
		{
			f_right = point.f;
		}
		point.z = point.f;
		coordinats.dim--;
		infoPoints.push_back(point);
			if (f_left > f_right)
			{
				currentMin = f_right;
				currentMax = f_left;

			}
			else
			{
				currentMax = f_right;
				currentMin = f_left;

			}
		

		// cout <<point;
		double eps = infoPoints[1].x - infoPoints[0].x;

		while (eps > epsilon)
		{
			int num = p_method->findR(infoPoints, r);
			//найти интервал с лучшей характеристикой
			//найти точку на этом интервале, в кот проводить испытание
			point.x = p_method->getX(infoPoints, num, r);
			coordinats.x[coordinats.dim] = point.x;
			coordinats.dim++;
			point.f = extremum(function, coordinats, coordinatsMin, epsilon, r, mon);
			point.z = point.f;
			if (point.f < currentMin)
			{
				currentMin = point.f;
			}
			if (point.f > currentMax)
			{
				currentMax = point.f;
			}
			coordinats.dim--;
			//вставить в нужное место в векторе
			infoPoints.insert(infoPoints.begin() + num + 1, point);//возможно num + 1
			if (mon == 1) {
				if ((infoPoints.front().f != currentMin) && (infoPoints.back().f != currentMin))// здесь нужно проверить что бы минимум не был в первой точке && в последней точке)
				{
					for (int i = 0; i < infoPoints.size(); i++) {//по всему вектору z
						infoPoints[i].z = sqrt(infoPoints[i].f - currentMin);//минус f min
					}
				}
			}

			if (mon == 2) {
				if ((infoPoints.front().f != currentMin) && (infoPoints.back().f != currentMin))// здесь нужно проверить что бы минимум не был в первой точке && в последней точке)
				{
					for (int i = 0; i < infoPoints.size(); i++) {//по всему вектору z
						infoPoints[i].z = sqrt(1 - pow((1 - ((infoPoints[i].f - currentMin) / (currentMax - currentMin))), 2));//минус f min)/(f max-f min))),2
						
					}

				}
			}
			eps = infoPoints[num + 1].x - infoPoints[num].x;

		}
		/*coordinats.dim--;*/
		count++;
	}//


	else
	{
		vectorCoordinat res = coordinats;
		res.z = function.FindFunction(coordinats.x);
		for (auto i : coordinats.x)
			cout <<"x = " << i << endl;
		cout <<"z = " << res.z << endl;
		//сохраняем данные в удобный формат для записи в файл
		storeData(res);
		if (coordinatsMin.dim == -1)
		{
			coordinatsMin = res;
		}
		//здесь сравнивать с минимумом
		else if (coordinatsMin.z > res.z)
		{
			coordinatsMin = res;
			/*coordinats.dim -= 2;
			point.f = point.z = res.z;
			coordinats.dim += 2;*/
		}
		//return res;

		return res.z;
	}


}
void CExtremum::functionToFile(CFunction &funcion)
{
	std::fstream data("func.txt", ios::out);
	vector <double> x1;
	vector <double> x2;
	vector <double> z;
	vectorCoordinat coordin;
	coordin.x.resize(funcion.dim);
	coordin.dim = 0;
	double left = funcion.LeftX(coordin.dim);
	double _left = funcion.RightX(coordin.dim);
	coordin.dim++;
	double right = funcion.LeftX(coordin.dim);
	double _right = funcion.RightX(coordin.dim);
	coordin.dim--;
	double step = (_left - left) / 100;
	double _step = (_right - right) / 100;
	double d = left, e, f;
	double eps = 0.001;
	do {
		e = right;
		for (int i = 0; i < 101; i++) {
			x1.push_back(d);
			x2.push_back(e);
			e += _step;
			if (fabs(e) < eps) {//считаем, что он равен нулю
				e = 0;
			}
		}
		d += step;
		if (fabs(d) < eps) {//считаем, что он равен нулю
			d = 0;
		}
	} while (d <= _left);
	data << "{";
	data << "\"x1" << "\": [";
	for (int i = 0; i < x2.size() - 1; i++) {
		data << x1[i] << ", ";
	}
	data << x1.back() << "], ";
	data << "\"x2" << "\": [";
	for (int i = 0; i < x2.size() - 1; i++) {
		data << x2[i] << ", ";
	}
	data << x2.back() << "], ";
	for (int i = 0; i < x2.size(); i++) {
		coordin.x[coordin.dim] = x1[i];
		coordin.dim++;
		coordin.x[coordin.dim] = x2[i];

		f = funcion.FindFunction(coordin.x);
		if (fabs(f) < eps) {//считаем, что он равен нулю
			f = 0;
		}
		z.push_back(f);

		coordin.dim--;
	}
	data << "\"z" << "\": [";
	for (int i = 0; i < z.size() - 1; i++) {
		data << z[i] << ", ";
	}
	data << z.back() << "]}";
	data.close();

}



void CExtremum::saveToFile()
{
	std::fstream file("data.txt", ios::out);

	unsigned int i = 1, j = 1;

	file << "{";
	for (auto coords : m_data)
	{
		file << "\"x" << i++ << "\": [";
		for (int i = 0; i < coords.size() - 1; ++i)
		{
			file << coords[i] << ", ";
		}
		file << coords.back() << "], ";
	}
	file << "\"z\": [";
	for (int i = 0; i < m_res.size() - 1; ++i)
	{
		file << m_res[i] << ", ";
	}
	file << m_res.back() << "]}";
	file.close();
}

vectorCoordinat CExtremum::extremum(CFunction &function, double epsilon, double r, int mon)
{
	vectorCoordinat coordinatsMin;
	coordinatsMin.dim = -1; // -1 что бы знать что мы ешё не находили минимальный вектор
	//найти coordinatsMin
	vectorCoordinat coordinats;
	coordinats.dim = 0;
	coordinats.x.resize(function.dim);
	for (size_t i = 0; i < function.GetDimention(); ++i)
		m_data.push_back(std::vector<double>());
	extremum(function, coordinats, coordinatsMin, epsilon, r, mon);
	functionToFile(function);
	saveToFile();
	//вывод
	for (auto i : coordinatsMin.x)
		//	int size = showSize(coordinatsMin);
		//	cout << "n= " << size<<endl;
		return coordinatsMin;
}
