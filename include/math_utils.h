#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stddef.h>
#include <stdbool.h>

// Function declarations
double safe_divide(double a, double b, bool *success);
long long factorial(int n);
double power(double base, int exponent);
void print_array_stats(const double *arr, size_t size);

// Math constants
#define PI 3.14159265358979323846
#define E  2.71828182845904523536

#endif // MATH_UTILS_H