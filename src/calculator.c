#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"

void print_menu(void) {
    printf("\n=== Modern C Calculator ===\n");
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Power\n");
    printf("6. Factorial\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main(void) {
    int choice;
    double a, b, result;
    int n;
    bool success;
    
    printf("Welcome to Modern C Calculator!\n");
    
    do {
        print_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter two numbers: ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("Result: %.2f\n", a + b);
                }
                break;
                
            case 2:
                printf("Enter two numbers: ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("Result: %.2f\n", a - b);
                }
                break;
                
            case 3:
                printf("Enter two numbers: ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    printf("Result: %.2f\n", a * b);
                }
                break;
                
            case 4:
                printf("Enter two numbers: ");
                if (scanf("%lf %lf", &a, &b) == 2) {
                    result = safe_divide(a, b, &success);
                    if (success) {
                        printf("Result: %.2f\n", result);
                    }
                }
                break;
                
            case 5:
                printf("Enter base and exponent: ");
                if (scanf("%lf %d", &a, &n) == 2) {
                    printf("Result: %.2f\n", power(a, n));
                }
                break;
                
            case 6:
                printf("Enter a number: ");
                if (scanf("%d", &n) == 1) {
                    long long fact = factorial(n);
                    if (fact >= 0) {
                        printf("Result: %lld\n", fact);
                    } else {
                        printf("Error: Cannot calculate factorial\n");
                    }
                }
                break;
                
            case 0:
                printf("Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice!\n");
                break;
        }
        
    } while (choice != 0);
    
    return EXIT_SUCCESS;
}