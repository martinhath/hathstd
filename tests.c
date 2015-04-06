#include "hathstd.h"

#include <stdio.h>
#include <string.h>

// test utils
void true(int a);
void eq(int a, int b);
void print_stats();

// tests
void test_list_push();
void test_list_pop_back();
void test_list_empty();
void test_list_pop_empty();


int main() {
    test_list_push();
    test_list_pop_back();
    test_list_empty();
    test_list_pop_empty();

    print_stats();
}

void test_list_push() {
    List *list = list_create();
    list_push(list, "martin");
    list_push(list, "er");
    list_push(list, "veldig");
    list_push(list, "kul");

    true(strcmp("kul", list_pop(list)) == 0);
    true(strcmp("veldig", list_pop(list)) == 0);
    true(strcmp("er", list_pop(list)) == 0);
    true(strcmp("martin", list_pop(list)) == 0);
    list_delete(list, 1);
}

void test_list_pop_back() {
    List *list = list_create();
    list_push(list, "martin");
    list_push(list, "er");
    list_push(list, "veldig");
    list_push(list, "kul");

    true(strcmp("martin", list_pop_back(list)) == 0);
    true(strcmp("er", list_pop_back(list)) == 0);
    true(strcmp("veldig", list_pop_back(list)) == 0);
    true(strcmp("kul", list_pop_back(list)) == 0);
    list_delete(list, 1);
}

void test_list_empty() {
    List *list = list_create();
    list_push(list, "halla");
    true(!list_empty(list));
    list_pop(list);
    true(list_empty(list));
}

void test_list_pop_empty() {
    List *list = list_create();
    list_push(list, "tom");
    list_pop(list);
    list_pop(list);
    true(1);
}


// Testing functions
static size_t N;
static size_t F;
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
    printf("Ran all tests.\n%zu/%zu passed.\n",
            N-F, N);
}
