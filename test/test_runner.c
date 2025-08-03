#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "math_utils.h"
#include "string_utils.h"
#include "file_utils.h"

// Simple test framework macros
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s - %s\n", __func__, message); \
            return false; \
        } \
    } while(0)

#define TEST_ASSERT_EQ(expected, actual, message) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAIL: %s - %s (expected: %g, got: %g)\n", \
                   __func__, message, (double)(expected), (double)(actual)); \
            return false; \
        } \
    } while(0)

#define TEST_ASSERT_NEAR(expected, actual, tolerance, message) \
    do { \
        double diff = fabs((double)(expected) - (double)(actual)); \
        if (diff > (tolerance)) { \
            printf("FAIL: %s - %s (expected: %g, got: %g, diff: %g)\n", \
                   __func__, message, (double)(expected), (double)(actual), diff); \
            return false; \
        } \
    } while(0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s... ", #test_func); \
        if (test_func()) { \
            printf("PASS\n"); \
            tests_passed++; \
        } else { \
            tests_failed++; \
        } \
        tests_total++; \
    } while(0)

// Global test counters
static int tests_total = 0;
static int tests_passed = 0;
static int tests_failed = 0;

// Test basic mathematical operations
bool test_math_basic_operations(void) {
    bool success;
    double result;
    
    // Test normal division
    result = safe_divide(10.0, 2.0, &success);
    TEST_ASSERT(success, "Division should succeed");
    TEST_ASSERT_NEAR(5.0, result, 1e-10, "10/2 should equal 5");
    
    // Test negative numbers
    result = safe_divide(-10.0, 2.0, &success);
    TEST_ASSERT(success, "Negative division should succeed");
    TEST_ASSERT_NEAR(-5.0, result, 1e-10, "-10/2 should equal -5");
    
    return true;
}

// Test edge cases and error conditions
bool test_math_edge_cases(void) {
    bool success;
    double result;
    
    // Test division by zero
    result = safe_divide(10.0, 0.0, &success);
    TEST_ASSERT(!success, "Division by zero should fail");
    TEST_ASSERT_EQ(0.0, result, "Division by zero should return 0");
    
    // Test division by very small number (near zero)
    result = safe_divide(10.0, 1e-15, &success);
    TEST_ASSERT(!success, "Division by near-zero should fail");
    
    // Test with NULL success pointer
    result = safe_divide(10.0, 2.0, NULL);
    TEST_ASSERT_NEAR(5.0, result, 1e-10, "Should work with NULL success pointer");
    
    return true;
}

// Test factorial function
bool test_math_factorial(void) {
    // Test normal cases
    TEST_ASSERT_EQ(1, factorial(0), "0! should equal 1");
    TEST_ASSERT_EQ(1, factorial(1), "1! should equal 1");
    TEST_ASSERT_EQ(2, factorial(2), "2! should equal 2");
    TEST_ASSERT_EQ(6, factorial(3), "3! should equal 6");
    TEST_ASSERT_EQ(24, factorial(4), "4! should equal 24");
    TEST_ASSERT_EQ(120, factorial(5), "5! should equal 120");
    
    // Test edge cases
    TEST_ASSERT_EQ(-1, factorial(-1), "Negative factorial should return -1");
    TEST_ASSERT_EQ(-1, factorial(25), "Large factorial should return -1 (overflow protection)");
    
    return true;
}

// Test power function
bool test_math_power(void) {
    // Test basic cases
    TEST_ASSERT_NEAR(1.0, power(5.0, 0), 1e-10, "Any number to power 0 should be 1");
    TEST_ASSERT_NEAR(5.0, power(5.0, 1), 1e-10, "5^1 should be 5");
    TEST_ASSERT_NEAR(25.0, power(5.0, 2), 1e-10, "5^2 should be 25");
    TEST_ASSERT_NEAR(125.0, power(5.0, 3), 1e-10, "5^3 should be 125");
    
    // Test negative exponents
    TEST_ASSERT_NEAR(0.2, power(5.0, -1), 1e-10, "5^-1 should be 0.2");
    TEST_ASSERT_NEAR(0.04, power(5.0, -2), 1e-10, "5^-2 should be 0.04");
    
    // Test negative base
    TEST_ASSERT_NEAR(4.0, power(-2.0, 2), 1e-10, "(-2)^2 should be 4");
    TEST_ASSERT_NEAR(-8.0, power(-2.0, 3), 1e-10, "(-2)^3 should be -8");
    
    return true;
}

// Test array statistics function
bool test_math_array_stats(void) {
    // Test normal array - we'll just test that it doesn't crash
    // since print_array_stats outputs to stdout
    double test_array[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    size_t size = sizeof(test_array) / sizeof(test_array[0]);
    
    printf("    Testing array stats output:\n    ");
    print_array_stats(test_array, size);
    
    // Test edge cases - should not crash
    print_array_stats(NULL, 0);
    print_array_stats(test_array, 0);
    
    return true;
}

// Test string utility functions
bool test_string_operations(void) {
    // Test safe_strdup
    const char *original = "Hello, World!";
    char *copy = safe_strdup(original);
    TEST_ASSERT(copy != NULL, "safe_strdup should not return NULL");
    TEST_ASSERT(strcmp(original, copy) == 0, "Duplicated string should match original");
    free(copy);
    
    // Test safe_strcpy
    char buffer[20];
    bool result = safe_strcpy(buffer, sizeof(buffer), "Hello");
    TEST_ASSERT(result, "safe_strcpy should succeed with adequate buffer");
    TEST_ASSERT(strcmp(buffer, "Hello") == 0, "Copied string should match");
    
    // Test safe_strcpy with insufficient buffer
    char small_buffer[3];
    result = safe_strcpy(small_buffer, sizeof(small_buffer), "Hello");
    TEST_ASSERT(!result, "safe_strcpy should fail with insufficient buffer");
    
    // Test email validation
    TEST_ASSERT(is_valid_email("user@example.com"), "Valid email should pass");
    TEST_ASSERT(!is_valid_email("invalid.email"), "Invalid email should fail");
    TEST_ASSERT(!is_valid_email("@invalid.com"), "Email without user should fail");
    TEST_ASSERT(!is_valid_email("user@"), "Email without domain should fail");
    
    return true;
}

// Test file utility functions  
bool test_file_operations(void) {
    const char *test_file = "test_temp_file.txt";
    const char *test_content = "This is test content\nLine 2\n";
    
    // Test writing to file
    bool written = write_string_to_file(test_file, test_content);
    TEST_ASSERT(written, "Should be able to write to file");
    
    // Test file exists
    TEST_ASSERT(file_exists(test_file), "File should exist after writing");
    
    // Test get file size
    long size = get_file_size(test_file);
    TEST_ASSERT(size > 0, "File size should be positive");
    TEST_ASSERT(size == (long)strlen(test_content), "File size should match content length");
    
    // Test reading file
    char *content = read_entire_file(test_file);
    TEST_ASSERT(content != NULL, "Should be able to read file");
    TEST_ASSERT(strcmp(content, test_content) == 0, "Read content should match written content");
    free(content);
    
    // Clean up test file
    remove(test_file);
    
    return true;
}

int main(void) {
    printf("=== Modern C Test Suite ===\n\n");
    
    // Run math utility tests
    printf("Math Utility Tests:\n");
    RUN_TEST(test_math_basic_operations);
    RUN_TEST(test_math_edge_cases);
    RUN_TEST(test_math_factorial);
    RUN_TEST(test_math_power);
    RUN_TEST(test_math_array_stats);
    
    printf("\nString Utility Tests:\n");
    RUN_TEST(test_string_operations);
    
    printf("\nFile Utility Tests:\n");
    RUN_TEST(test_file_operations);
    
    // Print summary
    printf("\n=== Test Summary ===\n");
    printf("Total tests: %d\n", tests_total);
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Success rate: %.1f%%\n", tests_total > 0 ? (100.0 * tests_passed / tests_total) : 0.0);

    return (tests_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
