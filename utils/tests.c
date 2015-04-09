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

    list = str_split("a b c d ", " ");
    true(list_size(list) == 4);
    list_foreach(list, free);
    list_free(list);

    list = str_split("  1    2 3 9 ", " ");
    true(list_size(list) == 4);
    int t = list_contains(list, "1", stringcmp) &
            list_contains(list, "2", stringcmp) &
            list_contains(list, "3", stringcmp) &
            list_contains(list, "9", stringcmp);
    true(t);
    list_foreach(list, free);
    list_free(list);

    list = str_split("hello", "non existant");
    true(list_size(list) == 1);
    char *str = list_pop(list);
    true(strcmp(str, "hello")== 0);
    list_free(list);
    free(str);
}

