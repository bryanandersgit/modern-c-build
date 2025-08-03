#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef _WIN32
    #define HAVE_SECURE_FUNCTIONS 1
#elif defined(__STDC_LIB_EXT1__) && __STDC_LIB_EXT1__
    #define HAVE_SECURE_FUNCTIONS 1
#else
    #define HAVE_SECURE_FUNCTIONS 0
#endif

// Include this at the top to enable secure functions
#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS 0
#endif

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

char *safe_strdup(const char *src) {
    if (!src) return NULL;

    size_t len = strlen(src);
    char *dest = malloc(len + 1);
    if (!dest) return NULL;

#if HAVE_SECURE_FUNCTIONS
#ifdef _WIN32
    if (memcpy_s(dest, len + 1, src, len + 1) != 0) {
        free(dest);
        return NULL;
    }
#else
    if (memcpy_s(dest, len + 1, src, len + 1) != 0) {
        free(dest);
        return NULL;
    }
#endif
#else
    // Manual byte-by-byte copy
    for (size_t i = 0; i <= len; i++) {
        dest[i] = src[i];
    }
#endif

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

#if HAVE_SECURE_FUNCTIONS
#ifdef _WIN32
    return strncpy_s(dest, dest_size, src, _TRUNCATE) == 0;
#else
    return strncpy_s(dest, dest_size, src, dest_size - 1) == 0;
#endif
#else
    // Manual character-by-character copy
    for (size_t i = 0; i <= src_len; i++) {
        dest[i] = src[i];
    }
    return true;
#endif
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
