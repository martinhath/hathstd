#include "hathstd.h"

#include <stdio.h>
#include <string.h>

// test utils
void true(int a);
void eq(int a, int b);
void print_stats();
void print(void*);
void println(void*);

// tests
void test_list_push();
void test_list_pop_back();
void test_list_empty();
void test_list_pop_empty();
void test_list_delete();

void test_array_add();
void test_array_set();
void test_array_get();
void test_array_resize();
void test_array_clone();

void test_hashmap();


int main() {
    printf("\n~~~ Testing List ~~~\n");
    test_list_push();
    test_list_pop_back();
    test_list_empty();
    test_list_pop_empty();
    test_list_delete();

    printf("\n~~~ Testing Array ~~~\n");
    test_array_set();
    test_array_get();
    test_array_add();
    test_array_resize();
    test_array_clone();

    printf("\n~~~ Testing HashMap ~~~\n");
    test_hashmap();

    print_stats();
}

void test_list_push() {
#ifdef DEBUG
    printf("test_list_push()\n");
#endif
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
#ifdef DEBUG
    printf("test_list_pop_back()\n");
#endif
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
#ifdef DEBUG
    printf("test_list_empty()\n");
#endif
    List *list = list_create();
    list_push(list, "halla");
    true(!list_empty(list));
    list_pop(list);
    true(list_empty(list));
    list_free(list);
}

void test_list_pop_empty() {
#ifdef DEBUG
    printf("test_list_pop_empty()\n");
#endif
    List *list = list_create();
    list_push(list, "tom");
    list_pop(list);
    list_pop(list);
    list_free(list);
    true(1);
}

int streq(void *s, void *t) {
    return strcmp(s, t) == 0;
}

void test_list_delete() {
#ifdef DEBUG
    printf("test_list_delete()\n");
#endif
    List *list = list_create();
    list_push(list, "martin");
    list_push(list, "er");
    list_push(list, "kul");
#ifdef DEBUG
    list_foreach(list, print);
#endif
    true(strcmp(list_delete(list, "er", streq), "er") == 0);
    list_free(list);
}


// end list

void println(void *s) {
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
    array_foreach(array, println);
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

void print(void *str) {
    printf("%s ", str);
}

void test_array_clone() {
    Array *array = array_create();
    array_add(array, "the");
    array_add(array, "quick");
    array_add(array, "brown");
    array_add(array, "fox");
    array_add(array, "jumped");

    printf("Print out original:\n");
    array_foreach(array, print);
    printf("\n");

    Array *copy = array_clone(array);

    printf("Print out copy:\n");
    array_foreach(copy, print);

    int res = 0;
    for (size_t i = 0; i < 4; i++) {
        void *a = array_get(array, i);
        void *b = array_get(copy, i);
        res |= strcmp(a, b) == 0;
    }
    true(res);
    printf("\n");
}

// HashMap
size_t int_hash(void *i) {
    return ((size_t) i) % 1024;
}

int key_cmp(void *s1, void *s2) {
    return s1 == s2;
}

void test_hashmap() {
    HashMap *hashmap = hashmap_create(int_hash, key_cmp);
    true(hashmap_set(hashmap, (void*) 100, "martin"));
    true(hashmap_set(hashmap, (void*) 1124, "er"));
    true(hashmap_set(hashmap, (void*) 2148, "kul"));

    char *str;
    str = hashmap_get(hashmap, (void*) 100);
    true(strcmp(str, "martin") == 0);
    str = hashmap_get(hashmap, (void*) 1124);
    true(strcmp(str, "er") == 0);
    str = hashmap_get(hashmap, (void*) 2148);
    true(strcmp(str, "kul") == 0);
}
// END HashMap

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
    printf("================\n");
    printf("Ran all tests.\n%zu/%zu passed.\n",
            N-F, N);
}

