#include "Hermite.hpp"

double accuracy = 0.00001;

Hermite::Hermite() {
	std::cout << STRING_HERMITE_NODES;
	std::cin >> nodeCount;
	std::cout << std::endl;
}

double Hermite::Calculate_Intepolation(PolynomialValues arr, Examples::Function* functions, const int& function) {

	Examples::Function functionPtr = functions[function];

	double result = 0, multiplier;
	for (int i = 0; i < 5; i++)
		if (arr[nodeCount - 2][i].weight != 0) {
			multiplier = arr[nodeCount - 2][i].weight * functionPtr(arr[nodeCount - 2][i].node);
			result += multiplier;
		}
	return result;
}

double Hermite::Calculate(PolynomialValues values, Examples::Function* functions, const int& function, const int& number) {

	Examples::Function functionPtr = functions[function];

	double result = 0, multiplier;
	for (int i = 0; i < 5; i++)
		if (values[nodeCount - 2][i].weight != 0) {
			multiplier =
				values[nodeCount - 2][i].weight * 
				functionPtr(values[nodeCount - 2][i].node) * 
				HermitePolynomial(number, values[nodeCount - 2][i].node);
			result += multiplier;
		}

	return result * Modulant(number);
}

double Hermite::Approximation(PolynomialValues values, Examples::Function* functions, const int& function, const double& x, const int& iter) {
	
	double factor, a, h;
	double result = 0;

	for (int i = 0; i <= iter; i++) {
		a = Calculate(values, functions, function, i);
		h = HermitePolynomial(i, x);
		factor = a*h;
		result += factor;
	}

	return result;
}

void Hermite::GetArray(PolynomialValues values) {

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++) {
			values[i][j].node = 0;
			values[i][j].weight = 0;
		}

	values[0][0].node = -0.707107; 
	values[0][0].weight = 0.886227;
	values[0][1].node = 0.707107;	
	values[0][1].weight = 0.886227;

	values[1][0].node = -1.224745; 
	values[1][0].weight = 0.295409;
	values[1][1].node = 0.000000;	
	values[1][1].weight = 1.181636;
	values[1][2].node = 1.224745;	
	values[1][2].weight = 0.295409;

	values[2][0].node = -1.650680; 
	values[2][0].weight = 0.081313;
	values[2][1].node = -0.534648; 
	values[2][1].weight = 0.804914;
	values[2][2].node = 0.534648;	
	values[2][2].weight = 0.804914;
	values[2][3].node = 1.650680;	
	values[2][3].weight = 0.081313;

	values[3][0].node = -2.020183; 
	values[3][0].weight = 0.019953;
	values[3][1].node = -0.958572; 
	values[3][1].weight = 0.393619;
	values[3][2].node = 0.000000;	
	values[3][2].weight = 0.945309;
	values[3][3].node = 0.958572;	
	values[3][3].weight = 0.393619;
	values[3][4].node = 2.020183;	
	values[3][4].weight = 0.019953;

}

void Hermite::GetPolynomials(double values[8][8]) {

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			values[i][j] = 0;

	values[0][0] = 1;
	values[1][1] = 2;
	values[2][0] = -2;
	values[2][2] = 4;

	values[3][1] = -12;
	values[3][3] = 8;

	values[4][0] = 12;
	values[4][2] = -48;
	values[4][4] = 16;

	values[5][1] = 120;
	values[5][3] = -160;
	values[5][5] = 32;

	values[6][0] = -120;
	values[6][2] = 720;
	values[6][4] = -480;
	values[6][6] = 64;

	values[7][1] = -1680;
	values[7][3] = 3360;
	values[7][5] = -1344;
	values[7][7] = 128;

	for (int i = 0; i < 8; i++) {
		std::cout << i << ": ";

		for (int j = 7; j >= 0; j--) {
			if (values[i][j] != 0)
				std::cout << values[i][j] << "x" << j << ", ";
		}

		std::cout << std::endl;
	}
}

std::string Hermite::GetFinalPolynomial(PolynomialValues values, Examples::Function* functions, const int& function, const int& iter) {

	double arrFinal[8] { 0 };
	double arrH[8][8];

	std::string result;

	GetPolynomials(arrH);

	for (int i = 0; i <= iter; i++) {
		double a = Calculate(values, functions, function, i);
		for (int j = 0; j < 8; j++) {
			//arrH[i][j] *= a;
			arrFinal[j] += arrH[i][j] * a;
		}
	}

	for (int i = 7; i >= 0; i--) {
		if (abs(arrFinal[i]) >= accuracy) {
			if (arrFinal[i] >= 0)
				result.append(" + ");
			else {
				result.append(" - ");
				arrFinal[i] = -arrFinal[i];
			}

			if (i == 0)
				result.append(std::to_string(arrFinal[i]));
			else if (i == 1) {
				result.append(std::to_string(arrFinal[i]));
				result.append("x");
			} else {
				result.append(std::to_string(arrFinal[i]));
				result.append("x^");
				result.append(std::to_string(i));
			}
		}
	}

	return result;
}

