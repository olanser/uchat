#include "client.h"

char *mx_str_insert(char *string, char *substr, int index_to) {
    int len = 0;
    char *new_str = 0;

    if (string == 0 && substr)
        return mx_strdup(substr);
    if (substr == 0 && string)
        return mx_strdup(string);
    if (substr == 0 && string == 0)
        return mx_strdup("");
    len = mx_strlen(string) + mx_strlen(substr) + 1;
    new_str = malloc(sizeof(char) * len);
    if (len < index_to)
        index_to = mx_strlen(string);
    memcpy(new_str, string, index_to);
    memcpy(&new_str[index_to], substr, mx_strlen(substr));
    memcpy(&new_str[index_to + mx_strlen(substr)], &string[index_to], mx_strlen(string) - index_to);
    new_str[len - 1] = 0;
    return new_str;
}
