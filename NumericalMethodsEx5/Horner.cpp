#include "Hermite.hpp"

double CalculateHorner(const double& x, double* factors, const int& factorsCount) {
	double result = 0.0;

	for (int i = 0; i < factorsCount; i++) {
		result *= x;
		result += factors[i];
	}

	return result;
}