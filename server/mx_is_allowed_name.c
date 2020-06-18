#include "header.h"

bool mx_is_allowed_name(char *str) {
    int i = -1;

    if (!((str[0] >= 65 && str[0] <= 90) 
        || (str[0] >= 97 && str[0] <= 122))) 
        return false;
    while (str[++i]) {
        if (!(((str[i] >= 65 && str[i] <= 90)
            || (str[i] >= 97 && str[i] <= 122))
            || (str[i] >= 48 && str[i] <= 57)))
            return false;
    }
    return true;
}
