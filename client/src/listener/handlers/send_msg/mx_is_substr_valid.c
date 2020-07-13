#include "client.h"
#include "defines_client.h"

static bool check_color(char *str) {
    int i = 0;

    for (int j = 0; j < 6; j++) {
        if (((str[++i] < 48) || (str[i] > 57)) // 0-10
            && ((str[i] < 65) || (str[i] > 70)) // A-F
            && ((str[i] < 97) || (str[i] > 102))) // a-f
            {
                return false;
            }
    }
    if (str[++i] != '\0') {
        return false;
    }
    return true;
}

static bool str_valid(char *str) {
    return (mx_strcmp(str, "b") == 0 
            || mx_strcmp(str, "big") == 0
            || mx_strcmp(str, "i") == 0
            || mx_strcmp(str, "s") == 0
            || mx_strcmp(str, "sub") == 0
            || mx_strcmp(str, "small") == 0
            || mx_strcmp(str, "tt") == 0
            || mx_strcmp(str, "u") == 0);
}

static bool check_tags(char *str, int end_format) {
    char *format = mx_strndup(str, end_format);
    char **tags = mx_strsplit(format, ' ');
    int i = -1;

    free(format);
    while (tags[++i]) {
        if (tags[i][0] == '#') {
            if (!check_color(tags[i])) {
                mx_del_strarr(&tags);
                return false;
            }
        }
        else if (!str_valid(tags[i])) 
            {
                mx_del_strarr(&tags);
                return false;
            }
    }
    mx_del_strarr(&tags);
    return true;
}

bool mx_is_substr_valid(char *substr) {
    int end = mx_get_char_index(substr, ':');
    
    if (end == -1) {// ':' dont finded
        return false;
    }
    if (!check_tags(substr, end))
        return false;

    return true;
}
