#include "libmx.h"

char *mx_strjoin_len(char *s1, char *s2, unsigned int len) {
    char *s = NULL;
    int a;

    if (s1 != 0 && s2 != 0) {
        s = mx_strnew(mx_strlen(s1) + len);
        a = mx_strlen(s1);
        if (s != 0){
            for (int i = 0 ; i < a; i++)
                s[i] = s1[i];
            for (unsigned int i = 0; i < len; a++, i++)
                s[a] = s2[i];
        }
        free(s1);
        return s;
    }
    if (s1 == 0 && s2 == 0)
        return 0;
    if (s1 != 0)
        return mx_strdup(s1);
    return mx_strndup(s2, len);
}
