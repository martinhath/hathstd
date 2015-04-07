#include "hathstd.h"

#include <stdio.h>

static HashNode *hashnode(void*, void*);
static int hashnode_cmp(void*, void*);

HashMap *hashmap_create(size_t (*hash)(void*),
        int (*keycmp)(void*, void*)) {
    HashMap *hashmap = emalloc(sizeof(HashMap));
    hashmap->hash = hash;
    hashmap->keycmp = keycmp;
    hashmap->array = emalloc(sizeof(List*) * _HASHMAP_CAP);
    for (size_t i = 0; i < _HASHMAP_CAP; i++)
        hashmap->array[i] = NULL;
    return hashmap;
}

int hashmap_set(HashMap *hashmap, void *key, void *val) {
    size_t i = hashmap->hash(key);
    List *list = hashmap->array[i];
    if (list == NULL) {
        hashmap->array[i] = list_create();
    }
    HashNode *hn = hashnode(key, val);
    // TODO: broken, can't update
    if (!list_contains(hashmap->array[i], hn, hashnode_cmp)) {
        list_push(hashmap->array[i], hn);
    }
    return 1;
}

void *hashmap_get(HashMap *hashmap, void *key) {
    size_t i = hashmap->hash(key);
    List *list = hashmap->array[i];
    // :(
    Node *node = list->head;
    while (node != NULL) {
        HashNode* hn = (HashNode*) node->val;
        if (hashmap->keycmp(key, hn->key)) {
            return hn->val;
        }
        node = node->next;
    }
    return NULL;
}

static int equals(void *a, void *b) {
    return a == b;
}

void *hashmap_delete(HashMap *hashmap, void *key) {
    size_t i = hashmap->hash(key);
    List *list = hashmap->array[i];
    if (list == NULL){
        return NULL;
    }
    Node *node = list->head;
    while (node != NULL) {
        HashNode* hn = (HashNode*) node->val;
        if (hashmap->keycmp(key, hn->key)) {
            list_delete(list, hn, equals);
            return hn->val;
        }
        node = node->next;
    }
    return NULL;
}

size_t hashmap_size(HashMap *hashmap) {
    size_t size = 0;
    for (size_t i = 0; i < _HASHMAP_CAP; i++) {
        List *list = hashmap->array[i];
        if (list != NULL) {
            size += list_size(list);
        }
    }
    return size;
}

void hashmap_free(HashMap *hashmap) {
    for (size_t i = 0; i < _HASHMAP_CAP; i++) {
        List *list = hashmap->array[i];
        if (list != NULL) {
            list_free(list);
        }
    }
}

static int hashnode_cmp(void *h1, void *h2) {
    HashNode *hn1 = (HashNode*) h1;
    HashNode *hn2 = (HashNode*) h2;
    return hn1->key == hn2->key && hn1->val == hn2->val;
}

static HashNode *hashnode(void *key, void *val) {
    HashNode *hn = emalloc(sizeof(HashNode));
    hn->key = key;
    hn->val = val;
    return hn;
}
