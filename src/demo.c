#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"
#include "string_utils.h"
#include "file_utils.h"

void demo_math_functions(void) {
    printf("=== Math Functions Demo ===\n");
    
    // Test division
    bool success;
    double result = safe_divide(15.5, 3.1, &success);
    printf("15.5 / 3.1 = %.2f (success: %s)\n", 
           result, success ? "true" : "false");
    
    // Test factorial
    printf("5! = %lld\n", factorial(5));
    printf("10! = %lld\n", factorial(10));
    
    // Test power
    printf("2^8 = %.0f\n", power(2.0, 8));
    printf("5^-2 = %.3f\n", power(5.0, -2));
    
    // Test array stats
    double numbers[] = {1.5, 2.8, 3.2, 4.1, 5.9, 2.3, 7.7, 1.1};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    print_array_stats(numbers, count);
    
    printf("\n");
}

void demo_string_functions(void) {
    printf("=== String Functions Demo ===\n");
    
    // Test string duplication
    const char *original = "Hello, Modern C!";
    char *copy = safe_strdup(original);
    printf("Original: '%s'\n", original);
    printf("Copy: '%s'\n", copy ? copy : "NULL");
    
    // Test string copying
    char buffer[50];
    bool copied = safe_strcpy(buffer, sizeof(buffer), original);
    printf("Safe copy: '%s' (success: %s)\n", 
           buffer, copied ? "true" : "false");
    
    // Test whitespace trimming
    char messy_string[] = "   Hello, World!   \n\t  ";
    printf("Before trim: '%s'\n", messy_string);
    char *trimmed = trim_whitespace(messy_string);
    printf("After trim: '%s'\n", trimmed);
    
    // Test email validation
    const char *emails[] = {
        "user@example.com",
        "invalid.email",
        "@invalid.com",
        "user@",
        "valid.user@domain.co.uk"
    };
    
    printf("Email validation:\n");
    for (size_t i = 0; i < sizeof(emails) / sizeof(emails[0]); i++) {
        printf("  '%s': %s\n", emails[i], 
               is_valid_email(emails[i]) ? "valid" : "invalid");
    }
    
    // Test string reversal
    char test_string[] = "Hello, World!";
    printf("Original: '%s'\n", test_string);
    reverse_string(test_string);
    printf("Reversed: '%s'\n", test_string);
    
    free(copy);
    printf("\n");
}

void demo_file_functions(void) {
    printf("=== File Functions Demo ===\n");
    
    const char *test_filename = "demo_test.txt";
    const char *test_content = "This is a test file created by the demo program.\n"
                              "It demonstrates file operations in modern C.\n"
                              "Line 3 of the test file.\n";
    
    // Write to file
    printf("Writing to file '%s'...\n", test_filename);
    bool written = write_string_to_file(test_filename, test_content);
    printf("Write result: %s\n", written ? "success" : "failed");
    
    // Check if file exists
    printf("File exists: %s\n", file_exists(test_filename) ? "yes" : "no");
    
    // Get file size
    long size = get_file_size(test_filename);
    printf("File size: %ld bytes\n", size);
    
    // Print file info
    print_file_info(test_filename);
    
    // Read file content
    printf("\nReading file content:\n");
    char *content = read_entire_file(test_filename);
    if (content) {
        printf("--- File Content ---\n%s--- End Content ---\n", content);
        free(content);
    } else {
        printf("Failed to read file content\n");
    }
    
    printf("\n");
}

int main(void) {
    printf("Modern C Utilities Demonstration\n");
    printf("================================\n\n");
    
    demo_math_functions();
    demo_string_functions();
    demo_file_functions();
    
    printf("Demo completed successfully!\n");
    printf("Note: You can clean up the demo_test.txt file if desired.\n");
    
    return EXIT_SUCCESS;
}
