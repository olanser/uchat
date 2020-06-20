#include "mxinet.h"

int mx_create_sock(int type) {
    int sock = socket(AF_INET, type, 0);
    
    if (sock == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        exit(1);
    }
    return 0;
}
