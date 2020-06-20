#include "header.h"

void mx_write_socket(int fd, char *response) {
    int size = *(int*)response;

    write(fd, response, size);
}
