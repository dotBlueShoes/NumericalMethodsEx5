#include "Functions.hpp"


double Examples::Function1(const double& x) {
	double result = 4 * x + 1;
	return result;
}

double Examples::Function2(const double& x) {
	double values[] { 4, 0, -2 };
	double result = CalculateHorner(x, values, 3);
	return result;
}

double Examples::Function3(const double& x) {
	double result = abs(x);
	return result;
}


double Examples::Function4(const double& x) {
	double result = sin(x);
	return result;
}

double Examples::Function5(const double& x) {
	double result = cos(2 * x + 1); // 2x + 1
	return result;
}

bool IsContinue() {
	char input;

	do {
		std::cout << STRING_IS_CONTINUE;
		std::cin >> input;
	} while (input != 'y' && input != 'n');

	std::cout << std::endl;

	if (input == 'y')
		return true;

	return false;
}

double Power(double base, const int& to) {
	if (to == 0) return 1;
	else return base *= Power(base, to - 1);
}

double Factorial(const int& base) {
	if (base == 0) return 1;
	if (base < 0) return 0;

	int result = 1;
	for (int i = 1; i <= base; i++) {
		result *= i;
	}

	return result;
}

double Modulant(const int& number) {
	return 1 / (sqrt(M_PI) * Power(2, number) * Factorial(number));
}

double HermitePolynomial(const int& i, const double& x) {
	switch (i) {

		default:
		case 0: {
			return 1;
		} break;

		case 1: {
			return 2 * x;
		} break;

		case 2: {
			return 4 * Power(x, 2) - 2;
		} break;

		case 3: {
			return 8 * Power(x, 3) - 12 * x;
		} break;

		case 4: {
			return 16 * Power(x, 4) - 48 * Power(x, 2) + 12;
		} break;

		case 5: {
			return 32 * Power(x, 5) - 160 * Power(x, 3) + 120 * x;
		} break;

		case 6: {
			return 64 * Power(x, 6) - 480 * Power(x, 4) + 720 * Power(x, 2) - 120;
		} break;

		case 7: {
			return 128 * Power(x, 7) - 1344 * Power(x, 5) + 3360 * Power(x, 3) - 1680 * x;
		} break;

	}
}
