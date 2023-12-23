#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>
#include <algorithm>


class Matrix {
private:
	double** elements;
	double* indexes;
	int rows;
	int columns;

public:
	Matrix();
	Matrix(const int rows, const int columns, const std::initializer_list<double>& elements);
	Matrix(const int rows, const int columns, const std::vector<double>& values);

	Matrix(const Matrix& m);
	Matrix(Matrix&& m) noexcept;
	Matrix& operator=(const Matrix& m);
	Matrix& operator=(Matrix&& m) noexcept;
	~Matrix();

	std::vector<double> row(const int index) const;
	std::vector<double> col(const int index) const;
	void setRow(const int index, const std::vector<double>& a);
	void setCol(const int index, const std::vector<double>& a);
	void shiftRows(const int firstIndex, const int secondIndex);
	void shiftColumns(const int firstIndex, const int secondIndex);

	double*& operator[](const int row) { return elements[row]; }
	double* operator[](const int row) const { return elements[row]; }

	Matrix T() const;
	void realign();		//aligns columns in their original order
	Matrix solve() const;

	void show() const;
	int nrows() const { return this->rows; }
	int ncols() const { return this->columns; }

};