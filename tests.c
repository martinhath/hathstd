#include "tests.h"

#include "containers/tests.h"
#include "utils/tests.h"

#include <stdio.h>
#include <stddef.h>
#include <string.h>

int main() {
    // entry points for tests.
    test_containers();
    test_utils();

    print_stats();
}

static size_t N;
static size_t F;

int ptrcmp(void *a, void *b) {
    return a==b;
}

int stringcmp(void *a, void *b) {
    return strcmp((char*) a, (char*) b);
}

void print(void *str) {
    printf("'%s' ", str);
}

void println(void *s) {
    printf("%s\n", s);
}

void true(int a) {
    N++;
    if (a == 1)
        return;
    printf("eq failed!:\na=%d\n", a);
    F++;
}

void eq(int a, int b) {
    N++;
    if (a == b)
        return;
    printf("eq2 failed!:\na=%d\tb=%d\n", a, b);
    F++;
}

void print_stats() {
    printf("\n\n================\n");
    printf("Ran all tests.\n%zu/%zu passed.\n",
            N-F, N);
}

