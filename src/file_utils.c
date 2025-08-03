#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

bool file_exists(const char *filepath) {
    if (!filepath) return false;
    
    struct stat st;
    return stat(filepath, &st) == 0;
}

long get_file_size(const char *filepath) {
    if (!filepath) return -1;
    
    struct stat st;
    if (stat(filepath, &st) != 0) {
        return -1;
    }
    
    return st.st_size;
}

char *read_entire_file(const char *filepath) {
    if (!filepath) return NULL;
    
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file '%s': %s\n", filepath, strerror(errno));
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (size < 0) {
        fprintf(stderr, "Error getting file size for '%s'\n", filepath);
        fclose(file);
        return NULL;
    }
    
    // Allocate buffer
    char *buffer = malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Error allocating memory for file '%s'\n", filepath);
        fclose(file);
        return NULL;
    }
    
    // Read file
    size_t bytes_read = fread(buffer, 1, size, file);
    fclose(file);
    
    if (bytes_read != (size_t)size) {
        fprintf(stderr, "Error reading file '%s'\n", filepath);
        free(buffer);
        return NULL;
    }
    
    buffer[size] = '\0'; // Null-terminate
    return buffer;
}

bool write_string_to_file(const char *filepath, const char *content) {
    if (!filepath || !content) return false;
    
    FILE *file = fopen(filepath, "w");
    if (!file) {
        fprintf(stderr, "Error opening file '%s' for writing: %s\n", 
                filepath, strerror(errno));
        return false;
    }
    
    size_t content_len = strlen(content);
    size_t bytes_written = fwrite(content, 1, content_len, file);
    fclose(file);
    
    if (bytes_written != content_len) {
        fprintf(stderr, "Error writing to file '%s'\n", filepath);
        return false;
    }
    
    return true;
}

void print_file_info(const char *filepath) {
    if (!filepath) {
        printf("Invalid filepath\n");
        return;
    }
    
    struct stat st;
    if (stat(filepath, &st) != 0) {
        printf("File '%s' does not exist or cannot be accessed\n", filepath);
        return;
    }
    
    printf("File Information for '%s':\n", filepath);
    printf("  Size: %ld bytes\n", st.st_size);
    printf("  Type: ");
    
    if (S_ISREG(st.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("Symbolic link\n");
    } else {
        printf("Special file\n");
    }
    
    printf("  Permissions: ");
    printf((st.st_mode & S_IRUSR) ? "r" : "-");
    printf((st.st_mode & S_IWUSR) ? "w" : "-");
    printf((st.st_mode & S_IXUSR) ? "x" : "-");
    printf((st.st_mode & S_IRGRP) ? "r" : "-");
    printf((st.st_mode & S_IWGRP) ? "w" : "-");
    printf((st.st_mode & S_IXGRP) ? "x" : "-");
    printf((st.st_mode & S_IROTH) ? "r" : "-");
    printf((st.st_mode & S_IWOTH) ? "w" : "-");
    printf((st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}