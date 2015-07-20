#include "tests.h"
#include "../tests.h"
#include "../hathstd.h"

#include <stddef.h>
#include <stdio.h>

void test_experimentals(void) {
    test_generator();
    test_generator_mul_two();
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

void *times_two(void *n) {
    long l = (long) n;
    return (void*) (l * 2);
}

void test_generator_mul_two() {
    Generator *gen = generator_create((void*) 1, times_two);
    printf("Doubles x 20 times, x_0 = 2:\n");
    for (size_t i = 2; i <= 20; i++) {
        printf("%d ", (int) generator_next(gen));
    }
    printf("\n");
}
