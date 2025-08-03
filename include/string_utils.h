#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include <stdbool.h>

// Safe string operations
char *safe_strdup(const char *src);
bool safe_strcpy(char *dest, size_t dest_size, const char *src);
char *trim_whitespace(char *str);
bool is_valid_email(const char *email);
void reverse_string(char *str);

#endif // STRING_UTILS_H