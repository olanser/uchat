#include "header.h"

static void mx_send_message2(int socket, char *response, int len) {
    if (socket < 0 || response == 0)
        return; // ERROR
    if (response[0] == 7)
    printf("\n\nYES\n\n");
    write(socket, response, len);
}

void mx_handle_out(int socket, int len, char **response) {
    if (len == 0)
        return;
    else {
        mx_send_message2(socket, *response , len);
    }
    free(*response);
}
