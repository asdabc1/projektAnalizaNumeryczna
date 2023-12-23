#include "Matrix.h"
#include <iostream>
#include <sstream>
#include <string>

Matrix gaussPodst(const Matrix& m);
Matrix gaussKol(const Matrix& m);
Matrix gaussPel(const Matrix& m);

Matrix manualInput();

enum {
	podstawowa = 0,
	maksKol = 1,
	maksPel = 2
};

Matrix przyklad1(4, 5, { 1,1,0,-3,1,1,4,-1,-4,-2,0.5,0.5,-3,-5.5,1.5,1.5,3,-5,-9,-0.5 });
Matrix przyklad2(4, 5, { 2.25,-2.5,4,-5.25,-1,-3,-7.5,6.5,0,17,-6.25,-12.5,0.25,5.25,24.25,9,10,7,-21,-33 });

int main() {
	using std::cout;
	using std::endl;
	using std::cin;

	int t;
	char te;

	Matrix sol;

	cout << "Podaj wykorzystywana metode (0 - podstawowa, 1 - przesuniecie kolumn, 2 - pelna): ";
	cin >> t;
	switch (t) {
	case podstawowa:
		cout << "macierz wprowadzana recznie czy przykladowa? (r/p)";
		cin >> te;
		if (te == 'p') {
			Matrix result = gaussPodst(przyklad1);
			sol = result.solve();
		}
		else
			gaussPodst(manualInput());
		break;

	case maksKol:
		cout << "macierz wprowadzana recznie czy przykladowa? (r/p)";
		if (cin.get() == 'p')
			gaussKol(przyklad2);
		else
			gaussKol(manualInput());
		break;

	case maksPel:
		cout << "macierz wprowadzana recznie czy przykladowa? (r/p)";
		if (cin.get() == 'p')
			gaussPel(przyklad2);
		else
			gaussPel(manualInput());
		break;

	default:
		cout << "wprowadzono nieprawidlowa wartosc!\n";
	}

	sol.show();

	return 0;
}

Matrix gaussPodst(const Matrix& m)
{
	Matrix temp(m);
	double p;
	int c = -1;
	std::vector<double> rw1, rw2;

	for (int i = 0; i < (m.ncols() > m.nrows() ? m.nrows() : m.ncols()); i++) {
		if (temp[i][i] == 0) {
			std::cout << "wartosc na przekatnej =0";
			return Matrix();
		}
	}

	for (int i = 0; i < temp.nrows() - 1; i++) {
		rw1 = temp.row(i);
		++c;

		for (int j = i+1; j < temp.nrows(); j++) {
			p = temp[j][i] / temp[i][i];
			rw2 = temp.row(j);
			
			for (int k = c; k < rw2.size(); k++)
				rw2[k] = rw2[k] - p * rw1[k];

			temp.setRow(j, rw2);
		}
	}

	return temp;
}

Matrix gaussKol(const Matrix& m)
{
	return Matrix();
}

Matrix gaussPel(const Matrix& m)
{
	return Matrix();
}

Matrix manualInput() {
	using std::cout;

	std::string temp;
	std::stringstream st;

	cout << "Podaj ilosc wierszy i kolumn (oddzielone spacja): ";
	std::cin.get();
	std::getline(std::cin, temp);
	st << temp;
	int a, b, c;
	st >> a >> b;

	std::vector<double> vals;

	cout << "Podaj elementy macierzy (oddzielone spacja, jednym ciagiem, wprowadzanie po wierszach)\n";
	
	std::cin.get();
	std::getline(std::cin, temp);
	st << temp;
	for (int i = 0; i < a * b; i++) {
		st >> c;
		vals.push_back(c);
	}

	return Matrix(a, b, vals);
}

