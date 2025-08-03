#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdbool.h>

// File operations
bool file_exists(const char *filepath);
long get_file_size(const char *filepath);
char *read_entire_file(const char *filepath);
bool write_string_to_file(const char *filepath, const char *content);
void print_file_info(const char *filepath);

#endif // FILE_UTILS_H