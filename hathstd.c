#include "hathstd.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

// Linked List implementation
List *list_create(void) {
    List *list = emalloc(sizeof(List));
    list->head = NULL;
    return list;
}

void list_free(List* list) {
    Node *n = list->head;
    while (n != NULL) {
        Node *tmp = n->next;
        free(n);
        n = tmp;
    }
    free(list);
}

// Pushed to the front
List *list_push(List *list, void *val) {
    Node *node = emalloc(sizeof(Node));
    Node *snd = list->head;
    list->head = node;
    node->next = snd;
    node->val = val;
    return list;
}

// Inserts at the back. Returns last element.
List *list_push_back(List *list, void *val) {
    Node *n = list->head;
    while (n->next != NULL)
        n = n->next;
    Node *node = emalloc(sizeof(Node));
    node->val = val;
    n->next = node;
    return list;
}

// Pops from the front
void *list_pop(List *list) {
    if (list_empty(list)) return NULL;
    Node *node = list->head;
    list->head = node->next;
    void *p = node->val;
    if (node == list->head)
        list->head = NULL;
    free(node);
    return p;
}

void *list_pop_back(List *list) {
    if (list_empty(list)) return NULL;
    Node *node = list->head;
    Node *prev = node;
    while (node->next != NULL) {
        prev = node;
        node = node->next;
    }
    prev->next = NULL;
    void *val = node->val;
    if (node == list->head)
        list->head = NULL;
    free(node);
    return val;
}

size_t list_size(List *list) {
    size_t c = 0;
    Node *node = list->head;
    while (node != NULL){
        node = node->next;
        c++;
    }
    return c;
}

int list_empty(List *list) {
    return list->head == NULL;
}

int list_contains(List* list, void *elem, int (*cmp)(void *a, void*b)) {
    Node *node = list->head;
    while (node != NULL) {
        if (cmp(elem, node->val))
            return 1;
        node = node->next;
    }
    return 0;
}

void list_foreach(List* list, void (*function)(void*)) {
    for (Node *node = list->head; node != NULL; node = node->next)
        function(node);
}

// End Linked List

// Safe Array
static void array_resize(Array*);
static void array_resize_to(Array*, size_t);
static int array_check_size(Array*, size_t);

Array *array_create(void) {
#define INIT_CAP 4
    Array *arr = emalloc(sizeof(Array));
    arr->capacity = INIT_CAP;
    arr->size = 0;
    arr->array = emalloc(sizeof(void*) * INIT_CAP);
    return arr;
}

void *array_get(Array *array, size_t i) {
    if (!array_check_size(array, i))
        return NULL;
    return array->array[i];
}

int array_set(Array *array, size_t i, void *elem) {
    if (!array_check_size(array, i))
        return 0;
    array->array[i] = elem;
    return 1;
}

int array_add(Array *array, void *elem) {
    if (array->size >= array->capacity)
        array_resize(array);
    array->size++;
    array_set(array, array->size-1, elem);
    return 1;
}

Array *array_clone(Array *array) {
    Array *arr = array_create();
    array_resize_to(arr, array->size);
    memmove(arr->array, array->array, array->size * sizeof(void*));
    arr->size = array->size;
    return arr;
}

void array_foreach(Array *array, void (*function)(void*)) {
    for (size_t i = 0; i < array->size; i++) {
        void *e = array_get(array, i);
        function(e);
    }
}

Array *array_map(Array *array, void* (*function)(void*)) {
    size_t n = array_size(array);
    Array *arr = array_create();
    array_resize_to(arr, n);
    for (size_t i = 0; i < n; i++) {
        void *e = function(array_get(array, i));
        array_add(arr, e);
    }
    return arr;
}

size_t array_size(Array *array) {
    return array->size;
}

void array_free(Array *array) {
    free(array->array);
    free(array);
}

static int array_check_size(Array *array, size_t i) {
    if (i >= array->size) {
#ifdef DEBUG
        fprintf(stderr, "[array_get] index out of bounds: index: %zu\
\tsize: %zu\n", i, array->size);
#endif
        return 0;
    }
    return 1;
}

static void array_resize(Array *array) {
    size_t cap = array->capacity * 1.5;
#ifdef DEBUG
    fprintf(stderr, "Resizing array at %p: %zu -> %zu\n",
            array, array->capacity, cap);
#endif
    void **arr = emalloc(cap * sizeof(void*));
    memmove(arr, array->array, array->size * sizeof(void*));
    free(array->array);
    array->array = arr;
    array->capacity = cap;
}

// does not pack!
static void array_resize_to(Array *array, size_t cap) {
    if (array->capacity >= cap) return;
    void **arr = emalloc(cap * sizeof(void*));
    memmove(arr, array->array, array->size * sizeof(void*));
    free(array->array);
    array->array = arr;
    array->capacity = cap;

}

// End Safe Array



// misc functions
void *emalloc(size_t s) {
    void *p = malloc(s);
    if (p == NULL) {
        fprintf(stderr, "[emalloc] Failed to allocate memory.");
        exit(2);
    }
    return p;
}
