#include "libmx.h"
#include "client.h"

static char *set_new_str(char *str_f, char *substr_f) {
    char *new_str = 0;

    if (str_f == 0 && substr_f){
        new_str = mx_strdup(substr_f);
    }
    else if (substr_f == 0 && str_f)
        new_str = mx_strdup(str_f);
    else if (substr_f == 0 && str_f == 0)
        new_str = mx_strdup("");
    return new_str;
}

char *mx_insert_str_between3(int start, int end, char*str_f, char*substr_f) {
    char *new_str = set_new_str(str_f, substr_f);
    int len = 0;

    if (new_str) {
        free(str_f);
        free(substr_f);
        return new_str;
    } 
    len = mx_strlen(str_f) - end + start + mx_strlen(substr_f) + 1;
    new_str = malloc(len);
    memset(new_str, 0, len);
    memcpy(new_str, str_f, start);
    memcpy(&new_str[start], substr_f, mx_strlen(substr_f));
    memcpy(&new_str[start + mx_strlen(substr_f)], &str_f[end], 
           mx_strlen(str_f) - end);
    free(str_f);
    free(substr_f);
    return new_str;
}