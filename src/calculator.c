#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
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

// Safe input reading functions
static int read_int(const char *prompt, int *value) {
    char buffer[32];
    char *endptr;
    long result;

    if (prompt && strlen(prompt) > 0) {
        printf("%s", prompt);
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0; // EOF or error
    }

    // Remove newline if present
    buffer[strcspn(buffer, "\n")] = '\0';

    errno = 0;
    result = strtol(buffer, &endptr, 10);

    // Check for conversion errors
    if (errno == ERANGE || result > INT_MAX || result < INT_MIN) {
        printf("Number out of range\n");
        return 0;
    }

    if (endptr == buffer || *endptr != '\0') {
        printf("Invalid number format\n");
        return 0;
    }

    *value = (int)result;
    return 1;
}

static int read_double(const char *prompt, double *value) {
    char buffer[64];
    char *endptr;
    double result;

    if (prompt && strlen(prompt) > 0) {
        printf("%s", prompt);
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0; // EOF or error
    }

    // Remove newline if present
    buffer[strcspn(buffer, "\n")] = '\0';

    errno = 0;
    result = strtod(buffer, &endptr);

    // Check for conversion errors
    if (errno == ERANGE) {
        printf("Number out of range\n");
        return 0;
    }

    if (endptr == buffer || *endptr != '\0') {
        printf("Invalid number format\n");
        return 0;
    }

    *value = result;
    return 1;
}

int main(void) {
    int choice = -1;
    double a, b, result;
    int n;
    bool success;

    printf("Welcome to Modern C Calculator!\n");

    do {
        print_menu();

        if (!read_int("", &choice)) {
            printf("Invalid input!\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter two numbers:\n");
                printf("First number: ");
                if (read_double("", &a)) {
                    printf("Second number: ");
                    if (read_double("", &b)) {
                        printf("Result: %.2f\n", a + b);
                    }
                }
                break;

            case 2:
                printf("Enter two numbers:\n");
                printf("First number: ");
                if (read_double("", &a)) {
                    printf("Second number: ");
                    if (read_double("", &b)) {
                        printf("Result: %.2f\n", a - b);
                    }
                }
                break;

            case 3:
                printf("Enter two numbers:\n");
                printf("First number: ");
                if (read_double("", &a)) {
                    printf("Second number: ");
                    if (read_double("", &b)) {
                        printf("Result: %.2f\n", a * b);
                    }
                }
                break;

            case 4:
                printf("Enter two numbers:\n");
                printf("First number: ");
                if (read_double("", &a)) {
                    printf("Second number: ");
                    if (read_double("", &b)) {
                        result = safe_divide(a, b, &success);
                        if (success) {
                            printf("Result: %.2f\n", result);
                        }
                    }
                }
                break;

            case 5:
                printf("Base: ");
                if (read_double("", &a)) {
                    printf("Exponent: ");
                    if (read_int("", &n)) {
                        printf("Result: %.2f\n", power(a, n));
                    }
                }
                break;

            case 6:
                printf("Enter a number: ");
                if (read_int("", &n)) {
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
