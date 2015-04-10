#ifndef HATHSTD_H
#define HATHSTD_H

#include <stddef.h>

////////////////
// Containers //
////////////////

// Linked List implementation
typedef struct ListNode {
    struct ListNode *next;
    void *val;
} ListNode;
typedef struct List {
    ListNode *head;
} List;


List *  list_create(void);
void    list_free(List*);
List *  list_push(List*, void*);
List *  list_push_back(List*, void*);
void *  list_pop(List*);
void *  list_pop_back(List*);
void *  list_delete(List*, void*, int (*cmp)(void*, void*));
List *  list_reverse(List*);
void    list_foreach(List*, void (*f)(void*));
int     list_empty(List*);
size_t  list_size(List*);
int     list_contains(List*, void*, int (*cmp)(void*, void*));

void *  list_iterator(List*);
void *  list_it_get(List*, void*);
void *  list_it_next(List*, void*);
int     list_it_end(List*, void*);
// TODO: void list_map(List*, void *(*f)(void*));
// End Linked List

// Safe Array
typedef struct Array {
    void ** array;
    size_t capacity;
    size_t size;
} Array;

Array * array_create(void);
void *  array_get(Array*, size_t);
int     array_set(Array*, size_t, void*);
int     array_add(Array*, void*);
Array * array_clone(Array*);
void    array_foreach(Array*, void (*f)(void*));
Array * array_map(Array*, void* (*f)(void*));
size_t  array_size(Array*);
int     array_contains(Array*, void*, int (*cmp)(void*, void*));
void *  array_delete(Array*, size_t);
void    array_free(Array*);


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

HashMap *   hashmap_create(size_t (*hash)(void*), int (*keycmp)(void*, void*));
HashMap *   hashmap_create_str(void);
void        hashmap_free(HashMap*);
int         hashmap_set(HashMap*, void*, void*);
void *      hashmap_get(HashMap*, void*);
void *      hashmap_delete(HashMap*, void*);
size_t      hashmap_size(HashMap*);
List *      hashmap_keys(HashMap*);
// HashMap End

// Tree

typedef struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
    void *data;
    int color: 1;
} TreeNode;

typedef struct Tree {
    TreeNode *root;
    int (*cmp)(void*, void*);
} Tree;

Tree *  tree_create(int (*cmp)(void*, void*));
void    tree_free(Tree* tree);
int     tree_insert(Tree*, void*);
void *  tree_delete(Tree*, void*);
int     tree_contains(Tree*, void*);
void    tree_foreach(Tree*, void (*f)(void*));
// Tree End

////////////////////
// Util functions //
////////////////////

void *emalloc(size_t s);

List *str_split(const char*, const char*);

#endif
