#include "hathstd.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Safe Array
static void array_resize(Array*);
static void array_resize_to(Array*, size_t);
static int array_check_size(Array*, size_t);

Array *array_create(void) {
#define INIT_CAP 1023
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

void *array_delete(Array *array, size_t i) {
    if (!array_check_size(array, i))
        return NULL;
    void *elem = array->array[i];
    memmove(array->array + i, array->array + i + 1, (array->size - i - 1) * sizeof(void*));
    array->size--;
    return elem;
}


int array_contains(Array *array, void* elem, int (*cmp)(void*, void*)) {
    for (size_t i = 0; i < array->size; i++)
        if (cmp(elem, array->array[i]))
            return 1;
    return 0;
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
