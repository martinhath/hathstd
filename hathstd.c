#include "hathstd.h"

#include <stdlib.h>
#include <stdio.h>

// Linked List implementation
List *list_create(void) {
    List *list = emalloc(sizeof(List));
    return list;
}

// Pushed to the front
List *list_push(List *list, void *val) {
    Node *node = emalloc(sizeof(Node));
    Node *head = list->head;
    list->head = node;
    node->next = head;
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
    Node *node = list->head;
    list->head = node->next;
    void *p = node->val;
    free(node);
    return p;
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

// End Linked List



// misc functions
void *emalloc(size_t s) {
    void *p = malloc(s);
    if (p == NULL) {
        fprintf(stderr, "[emalloc] Failed to allocate memory.");
        exit(2);
    }
    return p;
}
