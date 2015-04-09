#include "../hathstd.h"
#include "../tests.h"

#include "tests.h"

#include <stdio.h>
#include <string.h>


void test_containers() {
    printf("\n");
    printf("###########################\n");
    printf("### Testing containers/ ###\n");
    printf("###########################\n");
    printf("\n~~~ Testing List ~~~\n");
    test_list_push();
    test_list_push_back();
    test_list_pop_back();
    test_list_empty();
    test_list_pop_empty();
    test_list_delete();
    test_list_reverse();

    printf("\n~~~ Testing Array ~~~\n");
    test_array_set();
    test_array_get();
    test_array_add();
    test_array_map();
    test_array_delete();
    test_array_contains();
    test_array_clone();

    printf("\n~~~ Testing HashMap ~~~\n");
    test_hashmap();
    return;
    test_hashmap_update();
    test_hashmap_str_str();
    test_hashmap_delete();
    test_hashmap_size();
    test_hashmap_keys();
    test_hashmap_str();

    printf("\n~~~ Testing Tree ~~~\n");
    test_tree();
    test_tree_contains();
    test_tree_delete();
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

void test_list_push_back() {
    List *list = list_create();
    list_push_back(list, "std");
    list_push_back(list, "c");
    list_push_back(list, "kek");
    true(list_size(list) == 3);
    true(list_contains(list, "c", streq));
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
    if (s == NULL) return -1;
    if (t == NULL) return 1;
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
    true(strcmp(list_delete(list, "er", streq), "er") == 0);
    list_free(list);
}

void test_list_reverse() {
#ifdef DEBUG
    printf("test_list_reverse()\n");
#endif
    List *list = list_create();
    list_push(list, "martin");
    list_push(list, "linus");
    list_push(list, "rms");
    list_push(list, "kek");

    list_reverse(list);

    true(strcmp(list_pop(list), "martin") == 0);
    list_pop(list);
    list_pop(list);
    true(strcmp(list_pop(list), "kek") == 0);
    list_free(list);
}


// end list

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
    int ret = 1;
    ret &= array_add(array, "this");
    ret &= array_add(array, "is");
    ret &= array_add(array, "a");
    ret &= array_add(array, "test");
    ret &= array_add(array, "lel");
    ret &= array_add(array, "kek");
    true(ret == 1);
    array_free(array);
}

void *square(void *a) {
    size_t n = (size_t) a;
    return (void*) (n*n);
}

void test_array_map() {
    Array *array = array_create();
    for (size_t i = 0; i < 10; i++) {
        array_add(array, (void*) i + 1);
    }

    Array *squares = array_map(array, square);

    true(array_contains(squares, (void*) 81, ptrcmp));
    true(array_contains(squares, (void*) 100, ptrcmp));
    true(array_contains(squares, (void*) 49, ptrcmp));
    true(!array_contains(squares, (void*) 50, ptrcmp));
    true(!array_contains(squares, (void*) 30, ptrcmp));

    array_free(squares);
    array_free(array);
}

void test_array_delete() {
    Array *array = array_create();
    for (size_t i = 0; i < 10; i++) {
        array_add(array, (void*) i + 1);
    }

    size_t i = 5;
    void *e = array_delete(array, i);
    true(!array_contains(array, e, ptrcmp));
    array_free(array);
}

void test_array_contains() {
    Array *array = array_create();
    array_add(array, "martin");
    array_add(array, "er");
    array_add(array, "veldig");
    array_add(array, "kul");
    true(array_contains(array, "veldig", streq));
    true(!array_contains(array, "thoresen", streq));
    array_free(array);
}

void test_array_clone() {
    Array *array = array_create();
    array_add(array, "the");
    array_add(array, "quick");
    array_add(array, "brown");
    array_add(array, "fox");
    array_add(array, "jumped");

    Array *copy = array_clone(array);

    true(copy != array);
    true(copy->array != array->array);
    size_t n = array_size(array);
    for (size_t i = 0; i < n; i++) {
        char *str = array_get(array, i);
        char *cpy = array_get(copy, i);
        true(strcmp(str, cpy) == 0);
    }

    int res = 0;
    for (size_t i = 0; i < 4; i++) {
        void *a = array_get(array, i);
        void *b = array_get(copy, i);
        res |= strcmp(a, b) == 0;
    }
    true(res);
    printf("\n");
    array_free(array);
    array_free(copy);
}

// HashMap
size_t int_hash(void *i) {
    return ((size_t) i) % 1024;
}

int key_cmp(void *s1, void *s2) {
    return s1 == s2;
}

void test_hashmap() {
#ifdef DEBUG
    printf("test_hashmap()\n");
#endif
    HashMap *hashmap = hashmap_create(int_hash, key_cmp);

    true(hashmap_set(hashmap, (void*) 100, "martin"));
    hashmap_free(hashmap);
    return;
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

void test_hashmap_update() {
#ifdef DEBUG
    printf("test_hashmap_update()\n");
#endif
    HashMap *hashmap = hashmap_create(int_hash, key_cmp);
    hashmap_set(hashmap, (void*) 0, "zero");
    hashmap_set(hashmap, (void*) 1, "one");
    hashmap_set(hashmap, (void*) 0, "null");

    char *str = hashmap_get(hashmap, (void*) 0);
    true(strcmp(str, "null") == 0);

    hashmap_free(hashmap);
}

static size_t str_hash(void *p) {
    size_t hash = 0;
    char *str = p;
    char c;
    while((c = *str++) != '\0') {
        hash += c * 0xbabe;
    }
    return hash;
}

void test_hashmap_str_str() {
    HashMap *hashmap = hashmap_create(str_hash, streq);
    hashmap_set(hashmap, "martin", "kul");
    hashmap_set(hashmap, "webkom", "top kek");

    char *str;
    str = hashmap_get(hashmap, "martin");
    true(strcmp(str, "kul") == 0);
    str = hashmap_get(hashmap, "webkom");
    true(strcmp(str, "top kek") == 0);
    hashmap_free(hashmap);
}

void test_hashmap_delete() {
#ifdef DEBUG
    printf("test_hashmap_delete()\n");
#endif
    HashMap *hashmap = hashmap_create(int_hash, key_cmp);
    hashmap_set(hashmap, (void*) 12, "thoresen");
    hashmap_set(hashmap, (void*) 2, "martin");
    char *str;

    str = hashmap_delete(hashmap, (void*) 12);
    true(str != NULL);
    true(strcmp(str, "thoresen") == 0);

    str = hashmap_get(hashmap, (void*) 12);
    true(str == NULL);

    str = hashmap_delete(hashmap, (void*) 12);
    true(str == NULL);
    hashmap_free(hashmap);
}

void test_hashmap_size() {
    HashMap *hashmap = hashmap_create(int_hash, key_cmp);
    hashmap_set(hashmap, (void*) 0, "a");
    hashmap_set(hashmap, (void*) 1, "b");
    hashmap_set(hashmap, (void*) 2, "c");
    hashmap_set(hashmap, (void*) 3, "d");
    hashmap_set(hashmap, (void*) 4, "e");
    true(hashmap_size(hashmap) == 5);

    hashmap_delete(hashmap, (void*) 2);
    hashmap_delete(hashmap, (void*) 4);
    true(hashmap_size(hashmap) == 3);

    hashmap_delete(hashmap, (void*) 0);
    hashmap_delete(hashmap, (void*) 1);
    hashmap_delete(hashmap, (void*) 3);
    true(hashmap_size(hashmap) == 0);
    hashmap_free(hashmap);
}

void test_hashmap_keys() {
    HashMap *hashmap = hashmap_create(int_hash, key_cmp);
    hashmap_set(hashmap, (void*) 123, "bæ");
    hashmap_set(hashmap, (void*) 9001, "9001");
    hashmap_set(hashmap, (void*) 69, "lel");

    List *keys = hashmap_keys(hashmap);
    true(list_contains(keys, (void*) 69, key_cmp));
    true(list_contains(keys, (void*) 123, key_cmp));
    true(list_contains(keys, (void*) 9001, key_cmp));
    list_free(keys);
    hashmap_free(hashmap);
}

void test_hashmap_str() {
#ifdef DEBUG
    printf("test_hashmap_str()\n");
#endif
    HashMap *hashmap = hashmap_create_str();
    hashmap_set(hashmap, "en", "1");
    hashmap_set(hashmap, "to", "2");
    hashmap_set(hashmap, "tre", "3");
    true(hashmap_size(hashmap) == 3);
    hashmap_free(hashmap);
}
// END HashMap
// Tree

void test_tree() {
#ifdef DEBUG
    printf("test_tree()\n");
#endif
    Tree *tree = tree_create(streq);

    tree_insert(tree, "martin");
    tree_insert(tree, "ord");
    tree_insert(tree, "ting");
    tree_insert(tree, "lelel");
    tree_free(tree);
}

int strcmp2(void *s, void *t) {
    return strcmp((char*) s, (char*) t);
}

void test_tree_contains() {
#ifdef DEBUG
    printf("test_tree_contains()\n");
#endif
    Tree *tree = tree_create(strcmp2);
    tree_insert(tree, "martin");
    tree_insert(tree, "hath");
    tree_insert(tree, "c");
    tree_insert(tree, "ritchie");
    tree_insert(tree, "rms");
    tree_insert(tree, "torvalds");
    tree_insert(tree, "knuth");

    true(tree_contains(tree, "martin"));
    true(tree_contains(tree, "rms"));
    true(!tree_contains(tree, "kek"));
    tree_free(tree);
}

void test_tree_delete() {
#ifdef DEBUG
    printf("test_tree_delete()\n");
#endif
    char* strs[7] = {
        "c", "hath", "knuth", "martin",
        "ritchie", "rms", "torvalds"
    };
    size_t n = sizeof(strs)/sizeof(char*);
    Tree *tree = tree_create(strcmp2);
    for (size_t i = 0; i < n; i++) {
        tree_insert(tree, strs[i]);
    }

    for (size_t i = 0; i < n; i++) {
        tree_delete(tree, strs[i]);
        for (size_t j = 0; j <= i; j++) {
            true(!tree_contains(tree, strs[j]));
        }
        for (size_t j = i + 1; j < n; j++) {
            true(tree_contains(tree, strs[j]));
        }
    }
    tree_free(tree);
}
