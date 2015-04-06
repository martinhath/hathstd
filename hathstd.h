#include <stddef.h>

// Linked List implementation
typedef struct Node {
    struct Node *next;
    void *val;
} Node;
typedef struct List {
    Node *head;
} List;


List *list_create(void);
void list_free(List*);

List *list_push(List*, void*);
List *list_push_back(List*, void*);

void *list_pop(List*);
void *list_pop_back(List*);

void list_foreach(List*, void (*f)(void*));

int list_empty(List*);
size_t list_size(List*);
int list_contains(List*, void*, int (*cmp)(void*, void*));
// End Linked List

// Safe Array
typedef struct Array {
    void ** array;
    size_t capacity;
    size_t size;
} Array;

Array *array_create(void);

void *array_get(Array*, size_t);
int array_set(Array*, size_t, void*);
int array_add(Array*, void*);

void array_foreach(Array*, void (*f)(void*));
Array *array_map(Array*, void* (*f)(void*));

size_t array_size(Array*);

// TODO:
// int array_contains(Array*, void*, int (*cmp)(void*, void*));
// void *array_pop(size_t);
void array_free(Array*);

// Safe array end



// misc functions
void *emalloc(size_t s);

