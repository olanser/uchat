#include "client.h"
#include "defines_client.h"

static int get_start_index(char *str, int start) {
    int i = start;

    while (str[i]) {
        if (str[i] == '%' && str[i + 1] == '%')
            return i + 2;
        i++;
    }
    return -1; // we at the end of string
}

static int get_end_index(char *str, int start) {
    int i = start;

    while (str[i]) {
        if (str[i] == '%' && str[i + 1] == '%')
            return i;
        i++;
    }
    return -1; // we at the end of string
}

/* 
* get substr in pattern %%[some data]%%
* starting with i index
* return 0 if substr no finded
*/
char *mx_get_formated_substr(char *str, int *index, int *start_, int *end_) {
    char *substr = 0;
    int start = (*index);
    int end = (*index);

    if ((start = get_start_index(str, start)) == -1 
        || (end = get_end_index(str, start)) == -1)
        return 0;
    substr = mx_strndup(&str[start], end - start);
    *index = end;
    *start_ = start - 2;
    *end_ = end + 2;
    return substr;
}
