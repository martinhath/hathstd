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

void *list_delete(List*, void*, int (*cmp)(void*, void*));

void list_foreach(List*, void (*f)(void*));
// TODO: list_map

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

Array *array_clone(Array*);

void array_foreach(Array*, void (*f)(void*));
Array *array_map(Array*, void* (*f)(void*));

size_t array_size(Array*);

int array_contains(Array*, void*, int (*cmp)(void*, void*));

void *array_delete(Array*, size_t);

void array_free(Array*);

// Safe array end

// HashMap begin
typedef struct HashMap {
    List **array;
    size_t (*hash)(void*);
    int (*keycmp)(void*, void*);
} HashMap;

typedef struct HashNode {
    void *key;
    void *val;
} HashNode;

#define _HASHMAP_CAP 1024

HashMap *hashmap_create(size_t (*hash)(void*), int (*keycmp)(void*, void*));
void hashmap_free(HashMap*);

int hashmap_set(HashMap*, void*, void*);
void *hashmap_get(HashMap*, void*);

void *hashmap_delete(HashMap*, void*);

size_t hashmap_size(HashMap*);

List *hashmap_keys(HashMap*);
// HashMap End


// misc functions
void *emalloc(size_t s);

