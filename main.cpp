#include "Matrix.h"
#include <iostream>

int main() {
	Matrix x(2, 3, { 1, 2, 3, 4, 5, 6 });
	x.T().show();
	std::cout << std::endl;
	x.show();
	return 0;
}