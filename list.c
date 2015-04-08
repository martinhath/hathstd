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
    ListNode *n = list->head;
    while (n != NULL) {
        ListNode *tmp = n->next;
        free(n);
        n = tmp;
    }
    free(list);
}

// Pushed to the front
List *list_push(List *list, void *val) {
    ListNode *node = emalloc(sizeof(ListNode));
    ListNode *snd = list->head;
    list->head = node;
    node->next = snd;
    node->val = val;
    return list;
}

// Inserts at the back. Returns last element.
List *list_push_back(List *list, void *val) {
    if (list_empty(list))
        return list_push(list, val);
    ListNode *n = list->head;
    while (n->next != NULL)
        n = n->next;
    ListNode *node = emalloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    n->next = node;
    return list;
}

// Pops from the front
void *list_pop(List *list) {
    if (list_empty(list)) return NULL;
    ListNode *node = list->head;
    list->head = node->next;
    void *p = node->val;
    if (node == list->head)
        list->head = NULL;
    free(node);
    return p;
}

void *list_pop_back(List *list) {
    if (list_empty(list)) return NULL;
    ListNode *node = list->head;
    ListNode *prev = node;
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

void *list_delete(List *list, void *elem, int (*cmp)(void*, void*)) {
    ListNode *node = list->head;
    ListNode *prev = node;
    while (node != NULL) {
        if (cmp(elem, node->val)) {
            prev->next = node->next;
            if (list->head == node)
                list->head = NULL;
            return node->val;
        }
        prev = node;
        node = node->next;
    }
    return NULL;
}

size_t list_size(List *list) {
    size_t c = 0;
    ListNode *node = list->head;
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
    ListNode *node = list->head;
    while (node != NULL) {
        if (cmp(elem, node->val))
            return 1;
        node = node->next;
    }
    return 0;
}

List *list_reverse(List *list) {
    if (list_empty(list))
        return list;
    ListNode *prev = list->head;
    ListNode *node = prev->next;
    prev->next = NULL;
    while (node != NULL) {
        ListNode *n = node->next;
        node->next = prev;
        prev = node;
        node = n;
    }
    list->head = prev;
    return list;
}

void list_foreach(List *list, void (*function)(void*)) {
    for (ListNode *node = list->head; node != NULL; node = node->next)
        function(node->val);
}

// End Linked List
