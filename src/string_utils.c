#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *safe_strdup(const char *src) {
    if (!src) return NULL;

    size_t len = strlen(src) + 1;
    char *dest = malloc(len);
    if (!dest) return NULL;

    memcpy(dest, src, len);
    return dest;
}

bool safe_strcpy(char *dest, size_t dest_size, const char *src) {
    if (!dest || !src || dest_size == 0) {
        return false;
    }

    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        return false; // Not enough space
    }

    strcpy(dest, src);
    return true;
}

char *trim_whitespace(char *str) {
    if (!str) return NULL;

    // Trim leading whitespace
    while (isspace(*str)) {
        str++;
    }

    if (*str == '\0') {
        return str; // String is all whitespace
    }

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end--;
    }
    *(end + 1) = '\0';

    return str;
}

bool is_valid_email(const char *email) {
    if (!email) return false;

    // Simple email validation - just check for @ and .
    const char *at_pos = strchr(email, '@');
    if (!at_pos) return false;

    const char *dot_pos = strrchr(email, '.');
    if (!dot_pos) return false;

    // @ should come before the last .
    if (at_pos >= dot_pos) return false;

    // Should have characters before @, between @ and ., and after .
    if (at_pos == email) return false; // No characters before @
    if (at_pos + 1 == dot_pos) return false; // No characters between @ and .
    if (*(dot_pos + 1) == '\0') return false; // No characters after .

    return true;
}

void reverse_string(char *str) {
    if (!str) return;

    size_t len = strlen(str);
    if (len <= 1) return;

    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}
