#include "Matrix.h"

Matrix::Matrix() {
	rows = 0;
	columns = 0;
	elements = nullptr;
	indexes = nullptr;
}

Matrix::Matrix(const int a, const int b, const std::initializer_list<double>& e) {
	rows = a;
	columns = b;

	indexes = new double[columns];
	*elements = new double[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];

	auto temp = e.begin();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns && temp != e.end(); j++)
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

	*elements = new double[rows];
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

	*elements = new double[rows];
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
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] elements;
	delete[] indexes;
}