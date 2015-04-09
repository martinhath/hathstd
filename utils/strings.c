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
    while (string < end) {
        char *p = strstr(string, delimiter);
        if (p == NULL)
            p = (char*) end - 1;
        int n = p - string;
        if (n != 0) {
            char *str = emalloc(n * sizeof(char) + 1);
            memmove(str, string, n);
            str[n] = '\0';
            list_push(list, str);
        }
        string += n + delim_len;
    }
    list_reverse(list);
    return list;
}
