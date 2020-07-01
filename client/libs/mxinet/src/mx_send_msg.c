#include "mxinet.h"

int mx_send_msg(int socket, char *buff, int size) {
    return write(socket, buff, size);
}
