// sample.c
#include <hathstd.h>
#include <stdio.h>

void print(void*);

int main() {
    Array *array = array_create();
    array_add(array, "hath");
    array_add(array, "std");
    array_add(array, "just");
    array_add(array, "werks!");
    array_foreach(array, print);
    printf("\n");
    return 0;
}

void print(void *s) {
    printf("%s ", s);
}
