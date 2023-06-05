#pragma once

#include <iostream>
#include <cstring>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Functions.hpp"

#define STRING_HERMITE_NODES "Number of nodes for integral? [ 2 / 3 / 4 / 5 ]\n" "Option: "

const double accuracy = 0.00001;

struct Values {
	double node, weight;
};

using PolynomialValues = Values[4][5];

class Hermite {
private:
	int nodeCount;
public:
	double Approximation(PolynomialValues, Examples::Function*, const int&, const double&, const int&);
	double Calculate(PolynomialValues, Examples::Function*, const int&, const int&);
	void GetArray(PolynomialValues);
	void GetPolynomials(double[8][8]);
	std::string GetFinalPolynomial(PolynomialValues, Examples::Function*, const int&, const int&);
	Hermite();
};

