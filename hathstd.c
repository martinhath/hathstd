#include "hathstd.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

// misc functions
void *emalloc(size_t s) {
    void *p = malloc(s);
    if (p == NULL) {
        fprintf(stderr, "[emalloc] Failed to allocate memory.");
        exit(2);
    }
    return p;
}
