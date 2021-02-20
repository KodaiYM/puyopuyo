#include "function.h"
#include <cmath>

int Quotient(int a, int b) noexcept {
	return static_cast<int>(std::floor(static_cast<double>(a) / b));
}
int Remainder(int a, int b) noexcept {
	return a - Quotient(a, b) * b;
}
