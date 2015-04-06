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

void test_array_add();
void test_array_set();
void test_array_get();
void test_array_resize();


int main() {
    test_list_push();
    test_list_pop_back();
    test_list_empty();
    test_list_pop_empty();

    test_array_set();
    test_array_get();
    test_array_add();
    test_array_resize();

    print_stats();
}

void test_list_push() {
    List *list = list_create();
    list_push(list, "martin");
    list_push(list, "er");
    list_push(list, "veldig");
    list_push(list, "kul");

    true(list_size(list) == 4);

    true(strcmp("kul", list_pop(list)) == 0);
    true(strcmp("veldig", list_pop(list)) == 0);
    true(strcmp("er", list_pop(list)) == 0);
    true(strcmp("martin", list_pop(list)) == 0);
    true(list_size(list) == 0);
    list_free(list);
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
    list_free(list);
}

void test_list_empty() {
    List *list = list_create();
    list_push(list, "halla");
    true(!list_empty(list));
    list_pop(list);
    true(list_empty(list));
    list_free(list);
}

void test_list_pop_empty() {
    List *list = list_create();
    list_push(list, "tom");
    list_pop(list);
    list_pop(list);
    list_free(list);
    true(1);
}


// end list

void print(void *s) {
    printf("%s\n", s);
}

void test_array_set() {
    Array *array = array_create();
    array->size = 2;
    true(array_set(array, 0, "mar"));
    true(array_set(array, 1, "tin"));
    true(!array_set(array, 2, "NOT"));
    array_free(array);
}

void test_array_get() {
    Array *array = array_create();
    array->size = 2;
    array_set(array, 0, "mar");
    array_set(array, 1, "tin");
    true(strcmp(array_get(array, 0), "mar") == 0);
    true(strcmp(array_get(array, 1), "tin") == 0);
    true(strcmp(array_get(array, 1), "tin") == 0);
    true(array_get(array, 2) == NULL);
    array_free(array);
}

void test_array_add() {
    Array *array = array_create();
    array_add(array, "this");
    array_add(array, "is");
    array_add(array, "a");
    array_add(array, "test");
    array_add(array, "lel");
    array_add(array, "kek");
    array_foreach(array, print);
    array_free(array);
}

void *square(void *a) {
    size_t n = (size_t) a;
    return (void*) (n*n);
}

void test_array_resize() {
    Array *array = array_create();
    for (size_t i = 0; i < 10; i++) {
        array_add(array, (void*) i + 1);
    }

    printf("Printing numbers 1-10\n");
    for (size_t i = 0; i < 10; i++){
        size_t n = (size_t) array_get(array, i);
        printf("%zu ", n);
    }
    printf("\n");

    Array *squares = array_map(array, square);
    printf("Printing squares 1-10\n");
    for (size_t i = 0; i < 10; i++)
        printf("%zu ", (size_t) array_get(squares, i));

    printf("\n");
    array_free(squares);
    array_free(array);
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

