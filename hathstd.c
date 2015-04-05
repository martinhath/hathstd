#include "hathstd.h"

#include <stdlib.h>
#include <stdio.h>

// Linked List implementation
List *list_create(void) {
    List *list = emalloc(sizeof(List));
    list->head = NULL;
    return list;
}

void list_delete(List* list, int free_nodes) {
    if (free_nodes) {
        Node *n = list->head;
        while (n != NULL) {
            Node *tmp = n->next;
            free(n);
            n = tmp;
        }
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
    Node *node = list->head;
    list->head = node->next;
    void *p = node->val;
    if (node == list->head)
        list->head = NULL;
    free(node);
    return p;
}

void *list_pop_back(List *list) {
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
