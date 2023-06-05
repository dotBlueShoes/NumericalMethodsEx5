#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include "thirdparty/gnuplot_i.hpp"
#include "Functions.hpp"
#include "Hermite.hpp"

#define STRING_SEPERATOR		 "-----------------------------------\n"
#define STRING_SELECT_ACCURACY	 "Enter accuracy: "
#define STRING_SELECT_FUNCTION	 "\nChoose function:\n"
#define STRING_SELECT_AREA_BEGIN "Enter range START: "
#define STRING_SELECT_AREA_END	 "Enter range END: "
#define STRING_SELECT_NODE_COUNT "Enter count NODE: "
#define STRING_SELECT_POLY_POWER "Enter polynomial POWER: "
#define STRING_CALCULATED_POLY	 "\nCalculated polynomial is:\n"
#define STRING_APPROXIMATION_ERR "Approximation error is: "
#define STRING_GNUPLOT_TITLE	 "Approximation using Hermite Polynomials"

int main() {

	bool isContinue = true;

	do {

		int chosenFunction, howManyNodes, level;
		double begin, end;

		std::cout << STRING_SELECT_FUNCTION
			"\t[0] 4x+1\n"
			"\t[1] 4x^2 + x - 2\n"
			"\t[2] |x|\n"
			"\t[3] sin(x)\n"
			"\t[4] cos(2x+1)\n"
			"Option: ";

		std::cin >> chosenFunction;
		std::cout << "\n" STRING_SEPERATOR STRING_SELECT_ACCURACY;
		std::cin >> accuracy;
		std::cout << STRING_SELECT_AREA_BEGIN;
		std::cin >> begin;
		std::cout << STRING_SELECT_AREA_END;
		std::cin >> end;
		std::cout << STRING_SELECT_NODE_COUNT;
		std::cin >> howManyNodes;
		std::cout << STRING_SELECT_POLY_POWER;
		std::cin >> level;
		std::cout << '\n' << std::endl;
		

		{ // CALCULATING

			Examples::Function functions[] {
				Examples::Function1,
				Examples::Function2,
				Examples::Function3,
				Examples::Function4,
				Examples::Function5
			};

			Examples::Function functionPtr = functions[chosenFunction];
			PolynomialValues values;
			Hermite hermite;

			hermite.GetArray(values);

			std::cout << STRING_CALCULATED_POLY <<
				hermite.GetFinalPolynomial(values, functions, chosenFunction, level) <<
				'\n' << STRING_APPROXIMATION_ERR;

			double epsilon = 0;
			double diff = (abs(begin - end) / (howManyNodes - 1));

			for (double i = begin; i <= end; i += diff) {
				double part = functionPtr(i) - hermite.Approximation(values, functions, chosenFunction, i, level);
				double result = part * part;
				epsilon += result;
				std::cout << "r: " << result << std::endl;
			}

			std::cout << sqrt(epsilon) << std::endl;

			{ // PLOTTING
				Gnuplot plot;
				plot.set_title(STRING_GNUPLOT_TITLE);

				std::vector<double> baseX, baseY, resultX, resultY;
				for (double i = begin; i < end; i = i + 0.01) {
					baseX.push_back(i);
					baseY.push_back(functionPtr(i));
					resultX.push_back(i);
					resultY.push_back(hermite.Approximation(values, functions, chosenFunction, i, level));
				}

				plot.set_xlabel("x");
				plot.set_ylabel("f(x)");
				plot.set_grid();
				plot.set_xrange(-2, 2);
				plot.set_style("lines");
				plot.plot_xy(baseX, baseY, "Function");
				plot.plot_xy(resultX, resultY, "Approximation");
			}

		}

		isContinue = IsContinue();

	} while (isContinue == true);

	return 0;
}