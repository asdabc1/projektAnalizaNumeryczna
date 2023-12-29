#include "Matrix.h"

Matrix::Matrix() {
	rows = 0;
	columns = 0;
	elements = nullptr;
	indexes = nullptr;
}

Matrix::Matrix(const int rws, const int clmns, const std::initializer_list<double>& vals) {
	rows = rws;
	columns = clmns;

	indexes = new double[columns];
	elements = new double*[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];

	auto temp = vals.begin();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns && temp != vals.end(); j++)
			elements[i][j] = *(temp++);
	}

	for (int i = 0; i < columns; i++)
		indexes[i] = i;
}

Matrix::Matrix(const int rws, const int clmns, const std::vector<double>& vals) {
	rows = rws;
	columns = clmns;

	indexes = new double[columns];
	elements = new double*[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];

	auto temp = vals.begin();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns && temp != vals.end(); j++)
			elements[i][j] = *(temp++);
	}

	for (int i = 0; i < columns; i++)
		indexes[i] = i;
}

Matrix::Matrix(const Matrix& m) {
	for (int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] elements;
	delete[] indexes;

	rows = m.rows;
	columns = m.columns;

	indexes = new double[columns];

	for (int i = 0; i < columns; i++)
		indexes[i] = m.indexes[i];

	elements = new double*[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			elements[i][j] = m.elements[i][j];
	}
}

Matrix::Matrix(Matrix&& m) noexcept{
	if (reinterpret_cast<int>(elements) > 0 && reinterpret_cast<int>(indexes) > 0) {
		for (int i = 0; i < rows; i++)
			delete[] elements[i];
		delete[] elements;
		delete[] indexes;
	}

	rows = m.rows;
	columns = m.columns;
	elements = m.elements;
	indexes = m.indexes;

	m.rows = 0;
	m.columns = 0;
	m.elements = nullptr;
	m.indexes = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m) {
	for (int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] elements;
	delete[] indexes;

	rows = m.rows;
	columns = m.columns;

	indexes = new double[columns];

	for (int i = 0; i < columns; i++)
		indexes[i] = m.indexes[i];

	elements = new double*[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			elements[i][j] = m.elements[i][j];
	}

	return *this;
}

Matrix& Matrix::operator=(Matrix&& m) noexcept{
	if (reinterpret_cast<int>(elements) > 0 && reinterpret_cast<int>(indexes) > 0) {
		for (int i = 0; i < rows; i++)
			delete[] elements[i];
		delete[] elements;
		delete[] indexes;
	}

	rows = m.rows;
	columns = m.columns;
	elements = m.elements;
	indexes = m.indexes;

	m.rows = 0;
	m.columns = 0;
	m.elements = nullptr;
	m.indexes = nullptr;

	return *this;
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] elements;
	delete[] indexes;
}

std::vector<double> Matrix::row(const int index) const {
	std::vector<double> result;

	for (int i = 0; i < columns; i++)
		result.push_back(elements[index][i]);

	return result;
}

std::vector<double> Matrix::col(const int index) const {
	std::vector<double> result;

	for (int i = 0; i < rows; i++)
		result.push_back(elements[i][index]);

	return result;
}

Matrix& Matrix::setRow(const int index, const std::vector<double>& a) {
	auto temp = a.begin();

	for (int i = 0; i < columns && temp != a.end(); i++)
		elements[index][i] = *(temp++);

	return *this;
}

Matrix& Matrix::setCol(const int index, const std::vector<double>& a) {
	auto temp = a.begin();

	for (int i = 0; i < rows && temp != a.end(); i++)
		elements[i][index] = *(temp++);

	return *this;
}

Matrix& Matrix::shiftRows(const int firstIndex, const int secondIndex) {
	auto temp = row(firstIndex);
	this->setRow(firstIndex, row(secondIndex));
	this->setRow(secondIndex, temp);

	return *this;
}

Matrix& Matrix::shiftColumns(const int firstIndex, const int secondIndex) {
	auto temp = col(firstIndex);
	this->setCol(firstIndex, col(secondIndex));
	this->setCol(secondIndex, temp);
	std::swap(indexes[firstIndex], indexes[secondIndex]);

	return *this;
}

Matrix Matrix::T() const {
	std::vector<double> x;

	for (int j = 0; j < columns; j++) {
		for (int i = 0; i < rows; i++)
			x.push_back(elements[i][j]);
	}

	return Matrix(columns, rows, x);
}

Matrix& Matrix::realign() {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < columns; j++) {
			if (indexes[j] == i) {
				this->shiftColumns(i, j);
				break;
			}
		}
	}
	return *this;
}

Matrix Matrix::solve() const {
	for (int i = 0; i < rows; i++)
		if (elements[i][i] == 0) {
			std::cout << "element na przekatnej =0, nie mozna rozwiazac macierzy!\n";
			return Matrix();
		}
	std::vector<double> vals;
	int c = 0;
	vals.push_back(elements[rows - 1][columns - 1] / elements[rows - 1][columns - 2]);

	for (int i = rows - 2; i >= 0; i--, c++) {
		double r = elements[i][columns - 1];
		auto pt = vals.rbegin();

		for (int j = columns - 2; j >= columns - 2 - c && j >= 0; j--) {
			r -= elements[i][j] * (*pt++);
		}

		vals.insert(vals.begin(), r / elements[i][columns - 3 - c]);
	}

	Matrix result(1, rows, vals);

	for (int i = 0; i < rows; i++)
		result.indexes[i] = this->indexes[i];

	result.realign();

	return result.T();
}

void Matrix::show() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << elements[i][j] << '\t';

		std::cout << std::endl;
	}
}

std::ostream& operator<<(std::ostream& o, const Matrix& m) {
	m.show();
	return o;
}
