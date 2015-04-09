#include "../hathstd.h"
#include "../tests.h"

#include <stdio.h>
#include <string.h>

void test_str_split(void);
int stringcmp(void*, void*);
void true(int);

void test_str_split() {
    const char *string = "martin er kul";
    List *list = str_split(string, "er");
    true(list_contains(list, "martin ", stringcmp));
    true(list_contains(list, " kul", stringcmp));
    true(!list_contains(list, "kul", stringcmp));
    true(list_contains(list, "martin", stringcmp) |
        list_contains(list, "er", stringcmp) |
        list_contains(list, " er ", stringcmp) |
        list_contains(list, "er ", stringcmp) |
        list_contains(list, " er", stringcmp));
}

int stringcmp(void *p, void *q) {
    return strcmp((char*) p, (char*) q);
}

