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
void list_delete(List*, int);

List *list_push(List*, void*);
List *list_push_back(List*, void*);

void *list_pop(List*);
void *list_pop_back(List*);

int list_empty(List*);

int list_contains(List*, void*, int (*cmp)(void*, void*));
// End Linked List



// misc functions
void *emalloc(size_t s);

