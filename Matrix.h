#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>


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
	void setRow(const std::vector<double>& a);
	void setCol(const std::vector<double>& a);
	void shiftRows(const int firstIndex, const int secondIndex);
	void shiftColumns(const int firstIndex, const int secondIndex);

	Matrix T() const;

	void show() const;

};