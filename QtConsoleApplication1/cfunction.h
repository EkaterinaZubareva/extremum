#ifndef CFUNCTION_H
#define CFUNCTION_H
#include <vector>
#include <math.h>
#include <string>
#include <queue>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <tuple>

using namespace std;
class CFunction {
    std::queue<std::string> m_queue;
    int m_sizeOper = 0;

private:
    std::pair<bool,double> isDigit(const std::string& s);

    static bool isSymbols(char c);

    void add_elemets(string &function, int& m, int& n, char symbol);
    bool isSingle(string &function,int& m,int& n);
    std::vector<std::pair<double, double>> m_Diapons;
    //вектор для сохранения подсчетов
    std::vector<double> m_results;
    // векто для текущих точек
    std::vector<double> m_vars;
    std::vector<string> m_supported {"cos","sin","tg","ctg"};
    // [..] или х..
    double parseValue(std::string& val);
    double calcFunc(string func, double arg);
    double calc(double n, double m, char symbol);
public:
    CFunction(std::string func);
    void addDiaposon(std::pair<double,double> && diap) {m_Diapons.push_back(diap);}
    double calc();
    int dim = 0;
    int GetDimention()
    {
        return dim;
    }//размерность
    double LeftX(int dim)
    {
        return m_Diapons[dim].first;
    };//левая граница
    double RightX(int dim)
    {
        return m_Diapons[dim].second;
    };//правая граница
    double FindFunction(std::vector<double>& points)
    {
        m_vars = points;
        return calc();
    }
	//double findFunction(srd::vector<double>& points)
    bool checkFunction(std::string &function, int m, int n);
    void removeBrackets(std::string& function, int m, int n, bool last = false);
    bool parseFunction(std::string function);

};

#endif // CFUNCTION_H
