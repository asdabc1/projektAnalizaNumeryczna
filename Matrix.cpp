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
	for (int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] elements;
	delete[] indexes;

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
	for (int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] elements;
	delete[] indexes;

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

void Matrix::setRow(const std::vector<double>& a) {

}

void Matrix::setCol(const std::vector<double>& a) {

}

void Matrix::shiftRows(const int firstIndex, const int secondIndex) {

}

void Matrix::shiftColumns(const int firstIndex, const int secondIndex) {

}

Matrix Matrix::T() const {
	std::vector<double> x;

	for (int j = 0; j < columns; j++) {
		for (int i = 0; i < rows; i++)
			x.push_back(elements[i][j]);
	}

	return Matrix(columns, rows, x);
}

void Matrix::show() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << elements[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}