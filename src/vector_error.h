#ifndef VECTOR_ERROR_H
#define VECTOR_ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static inline void vector_error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

static inline void vector_assert(bool condition, const char* message) {
    if (condition) {
        vector_error(message);
    }
}
#endif

