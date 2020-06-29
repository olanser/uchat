#include "client.h"
#include "libmx.h"

int mx_h_show_users(char *response, t_info *info) {
    int i = 14;
    while (i < *(int*)&response[5]) {
        printf("nick = %s\n", &response[i]);
        i+=105;
    }
    return 0;
}
