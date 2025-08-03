#include <stdio.h>
#include <stdlib.h>

// Using modern C features
int main(void) {
    printf("Hello, Modern C Development!\n");
    printf("Compiled with: ");
    
#ifdef __GNUC__
    printf("GCC %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(__clang__)
    printf("Clang %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#else
    printf("Unknown compiler\n");
#endif

    printf("C Standard: %ldL\n", __STDC_VERSION__);
    
    return EXIT_SUCCESS;
}