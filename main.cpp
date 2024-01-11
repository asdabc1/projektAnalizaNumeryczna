#include "Matrix.h"
#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

Matrix gaussPodst(const Matrix& m);
Matrix gaussKol(const Matrix& m);
Matrix gaussPel(const Matrix& m);

Matrix manualInput();
void wywolanie(const Matrix& m, std::function<Matrix(Matrix const&)> f);
void wybor(const Matrix& eg, std::function<Matrix(Matrix const&)> f);

enum {
	podstawowa = 0,
	maksKol = 1,
	maksPel = 2,
	galeria = 3
};

const double eps = 1e-7;

const Matrix przyklad1(4, 5, { 1,1,0,-3,1,1,4,-1,-4,-2,0.5,0.5,-3,-5.5,1.5,1.5,3,-5,-9,-0.5 });
const Matrix przyklad2(4, 5, { 2.25,-2.5,4,-5.25,-1,-3,-7.5,6.5,0,17,-6.25,-12.5,0.25,5.25,24.25,9,10,7,-21,-33 });
const Matrix osobliwa(3, 3, {1, 2, 1, 3, -7, -2, 2, 4, 2});

int main() {
	using std::cout;
	using std::cin;

	int t;

	cout << "Podaj wykorzystywana metode (0 - podstawowa, 1 - przesuniecie kolumn, 2 - pelna, 3 - galeria przykladow): ";
	cin >> t;
	switch (t) {
	case podstawowa:
		
		wybor(przyklad1, gaussPodst);

		break;

	case maksKol:
		
		wybor(przyklad2, gaussKol);

		break;

	case maksPel:
		
		wybor(przyklad2, gaussPel);

		break;

	case galeria:
		
		cout << "pierwsza macierz przykladowa (wykorzystywana w metodzie podstawowej):\n"
			<< przyklad1
			<< "druga macierz przykladowa (wykorzystywana w metodach z elementem maksymalnym):\n"
			<< przyklad2
			<< "macierz osobliwa:\n"
			<< osobliwa
			<< std::endl;

		cin.get();
		break;

	default:
		cout << "wprowadzono nieprawidlowa wartosc!\n";
		cin.get();
	}

	cout << "nacisnij ENTER, aby zakonczyc\n";
	cin.get();
	return 0;
}

auto krok = [](Matrix& matrix, int a, int b) {
	if (std::fabs(matrix[a][a]) < eps) {
		std::cout << "element [" << a << "][" << a << "] jest =0!\n";
		throw std::invalid_argument("Na przekatnej znajduje sie 0!");
	}

	return (matrix[b][a] / matrix[a][a]);
	};

Matrix gaussPodst(const Matrix& m) {
	Matrix temp(m);
	double p;
	std::vector<double> rw1, rw2;

	for (int i = 0; i < temp.nrows() - 1; i++) {
		rw1 = temp.row(i);

		for (int j = i+1; j < temp.nrows(); j++) {
			p = krok(temp, i, j);

			if (std::fabs(p) < eps)
				continue;

			rw2 = temp.row(j);
			
			for (int k = i; k < rw2.size(); k++)
				rw2[k] = rw2[k] - p * rw1[k];

			temp.setRow(j, rw2);
		}
	}
	return temp;
}

Matrix gaussKol(const Matrix& m) {
	Matrix temp(m);
	double p;

	for (int i = 0; i < temp.nrows(); i++) {
		int max = i;
		double maxv = 0;

		for (int j = i; j < temp.ncols() - 1; j++) {
			if (std::fabs(temp[i][j]) > maxv) {
				max = j;
				maxv = std::fabs(temp[i][j]);
			}
		}

		if (i != max)
			temp.shiftColumns(i, max);

		for (int j = i + 1; j < temp.nrows(); j++) {
			p = krok(temp, i, j);

			if (std::fabs(p) < eps)
				continue;

			for (int k = 0; k < temp.ncols(); k++)
				temp[j][k] = temp[j][k] - temp[i][k] * p;
		}
	}
	return temp;
}

Matrix gaussPel(const Matrix& m) {
	Matrix temp(m);
	double p;

	for (int i = 0; i < temp.nrows(); i++) {
		int maxx = i, maxy = i;
		double maxv = 0;

		for (int j = i; j < temp.nrows(); j++) {
			for (int k = i; k < temp.ncols() - 1; k++) {
				if (std::fabs(temp[j][k]) > maxv) {
					maxx = j;
					maxy = k;
					maxv = std::fabs(temp[j][k]);
				}
			}
		}

		if (i != maxx)
			temp.shiftRows(i, maxx);
		if (i != maxy)
			temp.shiftColumns(i, maxy);

		for (int j = i + 1; j < temp.nrows(); j++) {
			p = krok(temp, i, j);

			if (std::fabs(p) < eps)
				continue;
			
			for (int k = 0; k < temp.ncols(); k++)
				temp[j][k] = temp[j][k] - temp[i][k] * p;
			
		}
	}
	return temp;
}

Matrix manualInput() {
	std::string temp;
	std::stringstream st;
	int a, b;

	std::cout << "Podaj ilosc wierszy i kolumn (oddzielone spacja): ";
	std::cin.get();
	std::getline(std::cin, temp, '\n');
	st << temp;
	st >> a >> b;

	std::cout << "Podaj elementy macierzy (oddzielone spacja, jednym ciagiem, wprowadzanie po wierszach)\n";
	
	std::vector<double> vals;
	double c;
	st = std::stringstream();
	std::getline(std::cin, temp, '\n');
	st << temp;
	for (int i = 0; i < a * b; i++) {
		st >> c;
		vals.push_back(c);
	}

	return Matrix(a, b, vals);
}

void wywolanie(const Matrix& m, std::function<Matrix(Matrix const&)> f) {
	Matrix sol = f(m);

	sol = sol.solve();
	sol.T().show();
}

void wybor(const Matrix& eg, std::function<Matrix(Matrix const&)> f) {
	char te;

	std::cout << "macierz przykladowa - p, macierz wprowadzana recznie - r, macierz osobliwa - o:\n_ (p, r lub o)\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	std::cin >> te;

	if (te == 'p') {
		wywolanie(eg, f);
		std::cin.get();
	}

	else if (te == 'r')
		wywolanie(manualInput(), f);

	else if (te == 'o') {
		wywolanie(osobliwa, f);
		std::cin.get();
	}

	else
		std::cout << "nieprawidlowy wybor\n";
}