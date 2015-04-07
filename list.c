#include "hathstd.h"

#include <stdlib.h>
#include <stdio.h>

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
