#include "hathstd.h"

#include <stdio.h>
#include <string.h>

// test utils
void eq(int a);
void eq2(int a, int b);
void print_stats();

// tests
void test_list_push();


int main() {
    test_list_push();
    print_stats();
}

void test_list_push() {
    List *list = list_create();
    list_push(list, "martin");
    list_push(list, "er");
    list_push(list, "veldig");
    list_push(list, "kul");

    eq(strcmp("kul", list_pop(list)));
    eq(strcmp("veldig", list_pop(list)));
    eq(strcmp("er", list_pop(list)));
    eq(strcmp("martin", list_pop(list)));
}


// Testing functions
static size_t N;
static size_t F;
void eq(int a) {
    N++;
    if (a == 0)
        return;
    printf("eq failed!:\na=%d\n", a);
    F++;
}

void eq2(int a, int b) {
    N++;
    if (a == b)
        return;
    printf("eq2 failed!:\na=%d\tb=%d\n", a, b);
    F++;
}

void print_stats() {
    printf("Ran all tests.\n%zu/%zu passed.\n",
            N-F, N);
}
