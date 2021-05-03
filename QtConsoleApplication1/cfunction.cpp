#include "cfunction.h"
#include <math.h>
#include <iostream>
#include <QString>

std::pair<bool, double> CFunction::isDigit(const string &s) //проверяет число ли это
{
	double res;
	bool success;
	res = QString(s.c_str()).toDouble(&success);
	return std::pair<bool, double>{success, res};

}

bool CFunction::isSymbols(char c)
{
	return c == '*' || c == '\\' || c == '+' || c == '-' || c == ')' || c == '(';
}

void CFunction::add_elemets(string &function, int &m, int &n, char symbol)
{
	while (true)
	{
		string funcSk = function.substr(m, n - m); //выделяем подстроку начиная с m символа в колличетсве n-m
		int posSym = funcSk.find(symbol); //ищем в строке знак
		// symbol * 2+34*56+3
		if (posSym != -1) // если найден пытаетмся вырезать левую и правую часть выражения
		{
			string first = funcSk.substr(0, posSym); // 2+34
			string second = funcSk.substr(posSym + 1); //56+3
			auto second_iter = std::find_if(second.begin(), second.end(), isSymbols); //ищем первый не символ
			auto first_iter = std::find_if(first.rbegin(), first.rend(), isSymbols); // ищем первый не символ слева
			if (first_iter != first.rend())
			{
				if (first_iter + 1 != first.rend())
				{
					if (first_iter != first.rend() && *(first_iter + 1) == '-' && *(first_iter + 2) == '(')
					{
						first_iter = first_iter + 1;
					}
				}
			}
			first = string(first.rbegin(), first_iter); //43
			first = string(first.rbegin(), first.rend()); //34
			second = string(second.begin(), second_iter); // 56
			m_queue.push(first);
			m_queue.push(string(1, symbol));
			m_queue.push(second);
			string number = string("[").append(to_string(m_sizeOper++)).append("]");//[0]
			function = function.substr(0, m + posSym - first.size()) + number + function.substr(m + posSym + second.size() + 1);
			//2+[0]+3 n изменялся
			n -= first.size() + second.size() + 1/*знак*/ - number.size();
			continue;
		}
		else
		{
			break;
		}
	}
}

bool CFunction::isSingle(string &function, int& m, int& n)
{
	string tmp = function.substr(m, n - m);
	if (isDigit(tmp).first)
	{
		m_queue.push("1");
	}
	else // одиночная переменная или [0]
	{
		tmp = function.substr(m, n - m); // tmp = -х1
		bool isNegative = tmp.at(0) == '-';
		if (isNegative)
		{
			tmp = string(tmp.begin() + 1, tmp.end()); //tmp = x1
		}
		auto iter = find_if(tmp.begin(), tmp.end(), isSymbols);
		if (iter != tmp.end()) // если есть какой то символ в строке то это точно не одиночное что то
		{
			return false;
		}
		else
		{
			if (isNegative)
				m_queue.push("-1");
			else
			{
				m_queue.push("1");
			}
		}
	}
	m_queue.push("*");
	m_queue.push(tmp);
	string number = string("[").append(to_string(m_sizeOper++)).append("]");
	function = function.substr(0, m) + number + function.substr(n);
	n = m + number.size();
	return true;
}

CFunction::CFunction(string func)
{
	parseFunction(func);
	m_results.reserve(m_queue.size() / 3);
}

double CFunction::parseValue(string &val)
{
	return val.front() == '[' ? // если начинается с [ то это [..] иначе х..
		m_results[std::stoul(val.substr(1))] :
		m_vars[std::stoul(val.substr(1)) - 1];
}

double CFunction::calcFunc(string func, double arg)
{
	switch (std::distance(m_supported.begin(), std::find(m_supported.begin(), m_supported.end(), func)))
	{
	case 0:
		return cos(arg);
	case 1:
		return sin(arg);
	case 2:
		return tan(arg);
	case 3:
		return 1 / tan(arg);
	default:
		std::cout << func << " - the function isn't supported abort";
		abort();
	}
}

double CFunction::calc(double n, double m, char symbol)
{
	switch (symbol)
	{
	case '*':
		return n * m;
	case '/':
		return n / m;
	case '+':
		return m + n;
	case '-':
		return n - m;
	}
}

double CFunction::calc()
{
	double n = 0, m = 0;
	double res = 0;
	std::queue<std::string> queue = m_queue;
	while (!queue.empty())
	{
		std::string first(queue.front());
		queue.pop();
		std::string symbol(queue.front());
		queue.pop();
		std::string second(queue.front());
		queue.pop();
		auto tmp = isDigit(first);
		n = tmp.first ? //если это цифра
			tmp.second :
			parseValue(first); // это либо х.. либо [..]
		tmp = isDigit(second);
		m = symbol == "&" ? //если функция то результат в m будет
			calcFunc(second, n) :
			tmp.first ? //если это цифра
			tmp.second :
			parseValue(second);
		res = symbol == "&" ?
			m :
			calc(n, m, symbol.at(0));
		m_results.push_back(res);
	}
	m_results.clear();
	return res;
	
}

bool CFunction::checkFunction(string &function, int m, int n)
{
	//case1: 2+([0]) case2: 2+cos([0])
	string tmp = function.substr(0, m - 1);//case1: 2+ case2:2+cos
	auto  iter = find_if(tmp.rbegin(), tmp.rend(), isSymbols); //ищем первый символ
	tmp = string(tmp.rbegin(), iter);//case1: пусто case2: soc
	tmp = string(tmp.rbegin(), tmp.rend()); //cos
	if (!tmp.empty()) // если не пустой то функция
	{
		m_queue.push(string("[").append(to_string(m_sizeOper - 1).append("]")));//[0]
		m_queue.push("&");
		m_queue.push(tmp);//cos
		string number = string("[").append(to_string(m_sizeOper++)).append("]"); //[1]
		function = function.substr(0, m - tmp.size() - 1) + number + function.substr(n + 1);
		return true;
	}
	return false;
}

void CFunction::removeBrackets(string &function, int m, int n, bool last)
{
	if (!isSingle(function, m, n)) // если это (12) (x1) ([0])
	{
		add_elemets(function, m, n, '*');
		add_elemets(function, m, n, '/');
		add_elemets(function, m, n, '+');
		add_elemets(function, m, n, '-');
	}
	if (function.find(')') != -1) //если нашли скобку
	{
		if (!checkFunction(function, m, n)) // проверяем функция ли это если нет то удаляем скобки
		{
			function.erase(m - 1, 1);
			function.erase(n - 1, 1);
		}

	}
}

bool CFunction::parseFunction(string function)
{
	while (true)//2+3*5+(2+5)
	{
		int n = function.find(')');
		if (n == -1)// больше скобок нет раскрвать нечего
		{
			break;
		}
		else
		{
			int m = function.substr(0, n).find_last_of('(');
			removeBrackets(function, m + 1, n);

		}
	}
	//2+3*5+[0]
	removeBrackets(function, 0, function.size()); //посчитаем с учетом что все скобки раскрыты
	return true;
}
