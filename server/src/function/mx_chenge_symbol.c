#include "server.h"

char *mx_chenge_symbol(char *str) {
    int symbol = 0;
    int sum = -1;
    char *new_str = 0;

    while (str[++sum]) {
        if (str[sum] == '\'')
            symbol++;
    }
    new_str = malloc(symbol + sum + 1);
    sum = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\'')
            new_str[sum++] = '\'';
        new_str[sum++] = str[i];
    }
    new_str[sum++] = 0;
    return new_str;
}
