#include "../hathstd.h"
#include "../tests.h"

#include "tests.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_utils() {
    printf("\n");
    printf("######################\n");
    printf("### Testing utils/ ###\n");
    printf("######################\n\n");
    test_str_split();
}

void test_str_split() {
#ifdef DEBUG
    printf("test_str_split()\n");
#endif
    List *list = str_split("martin er kul", "er");
    true(list_contains(list, "martin ", streq));
    true(list_contains(list, " kul", streq));
    true(!list_contains(list, "kul", streq));
    true(!(list_contains(list, "martin", streq) |
        list_contains(list, "er", streq) |
        list_contains(list, " er ", streq) |
        list_contains(list, "er ", streq) |
        list_contains(list, " er", streq)));
    list_foreach(list, free);
    list_free(list);
}

