#include "tests.h"
#include "../tests.h"
#include "../hathstd.h"

#include <stddef.h>

void test_experimentals(void) {
    test_generator();
}

void *add_one(void *n) {
    return n+1;
}

void test_generator(void) {
    Generator *gen = generator_create(0, add_one);
    printf("Printing 1-10:\n");
    for (size_t i = 1; i <= 10; i++) {
        printf("%d ", (int) generator_next(gen));
    }
    printf("\n");
}
