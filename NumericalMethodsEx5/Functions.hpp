#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cmath>

#include "Horner.hpp"

#define STRING_IS_CONTINUE "\nWanna Continue ? [ y / n ]: "

namespace Examples {
	using Function = double(*)(const double&);

	double Function1(const double& x);
	double Function2(const double& x);
	double Function3(const double& x);
	double Function4(const double& x);
	double Function5(const double& x);
}

bool IsContinue();
double Power(double, const int&);
double Factorial(const int&);
double Modulant(const int&);
double HermitePolynomial(const int&, const double&);