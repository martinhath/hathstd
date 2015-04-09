#include "hathstd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static HashNode *hashnode(void*, void*);
static int hashnode_cmp(void*, void*);

static size_t hash_str(void*);
static int str_cmp(void*, void*);

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

HashMap *hashmap_create_str() {
    return hashmap_create(hash_str, str_cmp);
}

int hashmap_set(HashMap *hashmap, void *key, void *val) {
    size_t i = hashmap->hash(key);
    List *list = hashmap->array[i];
    if (list == NULL) {
        hashmap->array[i] = list_create();
    }
    HashNode *hn = hashnode(key, val);
    list_delete(hashmap->array[i], hn, hashnode_cmp);
    list_push(hashmap->array[i], hn);
    return 1;
}

void *hashmap_get(HashMap *hashmap, void *key) {
    size_t i = hashmap->hash(key);
    List *list = hashmap->array[i];
    // Bad - uses the internals of List
    ListNode *node = list->head;
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
    // Bad - uses the internals of List
    ListNode *node = list->head;
    while (node != NULL) {
        HashNode* hn = (HashNode*) node->val;
        if (hashmap->keycmp(key, hn->key)) {
            list_delete(list, hn, equals);
            free(hn);
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

List *hashmap_keys(HashMap* hashmap) {
    List *keys = list_create();
    for (size_t j = 0; j < _HASHMAP_CAP; j++) {
        List *list = hashmap->array[j];
        if (list == NULL)
            continue;
        // Bad - uses the internals of List
        ListNode *node = list->head;
        while (node != NULL) {
            HashNode *hn = (HashNode*) node->val;
            list_push(keys, hn->key);
            node = node->next;
        }
    }
    return keys;
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

// Convenient default methods
static size_t hash_str(void *p) {
#define MUL 7
#define ACC 13
    size_t hash = 0;
    char *s = (char*) p;
    while (*s) {
        hash += *s * MUL + ACC;
        s++;
    }
    hash %= _HASHMAP_CAP;
    printf("hash('%s')\t= %zu\n", (char*) p, hash);
    return hash;
}

static int str_cmp(void *p, void *q) {
    return strcmp((char*) p, (char*) q);
}
