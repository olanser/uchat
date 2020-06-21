#include "server.h"

static bool check_null(char *str, int len) {
    int i = -1;

    while (len != ++i) {
        if (str[i] != 0)
            return 0;
    }
    return 1;
}

int mx_check_number(char *str, int len) {
    int i = -1;

    while (len != ++i) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            break;
    }
    if (i == len)
        return 0;
    if (check_null(&str[i], len - i))
        return 1;
    return 0;
}
