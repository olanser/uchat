#include "mxinet.h"

int mx_readn_sock(int socket, char *response, int size) {
    int count = 0;
    int curr = 0;

    while (curr < size) {
        count = read(socket, &response[curr], size - curr);
        
        if (count == -1 || count == 0) {
            fprintf(stderr, "SERVER CLOSED!\n");
            close(socket);
            exit(1);
        }
        curr += count;
    }
    return 0;
}
