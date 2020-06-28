#include "function.h"
#include <cmath>

int Quotient(int a, int b) {
	return (int)std::floor((float)a / b);
}
int Remainder(int a, int b) {
	return a - Quotient(a, b) * b;
}
