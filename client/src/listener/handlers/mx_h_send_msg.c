#include "client.h"
#include "libmx.h"

int mx_h_send_msg(char *response, t_info *info) {
    if (*(int*)&response[5] > 10) {
        printf("MSG!\n");
        printf("message = %s\n", &response[63]);
    }
    else {
        printf("ERR status = %d\n", response[9]);
    }
    return 0;
}
