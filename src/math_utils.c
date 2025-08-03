#include "math_utils.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

double safe_divide(double a, double b, bool *success) {
    if (success) *success = false;
    
    if (fabs(b) < 1e-10) {
        fprintf(stderr, "Error: Division by zero\n");
        return 0.0;
    }
    
    if (success) *success = true;
    return a / b;
}

long long factorial(int n) {
    if (n < 0) return -1;  // Error case
    if (n > 20) return -1; // Prevent overflow
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double power(double base, int exponent) {
    if (exponent == 0) return 1.0;
    
    double result = 1.0;
    int abs_exp = abs(exponent);
    
    for (int i = 0; i < abs_exp; i++) {
        result *= base;
    }
    
    return (exponent < 0) ? 1.0 / result : result;
}

void print_array_stats(const double *arr, size_t size) {
    if (!arr || size == 0) {
        printf("Empty array\n");
        return;
    }
    
    double sum = 0.0;
    double min = arr[0];
    double max = arr[0];
    
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    printf("Array Stats:\n");
    printf("  Size: %zu\n", size);
    printf("  Sum: %.2f\n", sum);
    printf("  Average: %.2f\n", sum / (double)size);
    printf("  Min: %.2f\n", min);
    printf("  Max: %.2f\n", max);
}