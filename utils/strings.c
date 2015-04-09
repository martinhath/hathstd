#include "../hathstd.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>

List *str_split(const char *string, const char *delimiter) {
    List *list = list_create();
    size_t delim_len = strlen(delimiter);
    const char *end = string;
    while (*end++)
        ;
    while (string <= end) {
        char *p = strstr(string, delimiter);
        int n = p - string;
        if (n < 0)
            n = end - string;
        char *str = emalloc(n * sizeof(char));
        memmove(str, string, n);
        list_push(list, str);
        string += n + delim_len;
    }
    list_reverse(list);
    return list;
}
