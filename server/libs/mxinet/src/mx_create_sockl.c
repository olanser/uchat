#include "mxinet.h"

static void check_listen(int sockl) {
    if (listen(sockl, SOMAXCONN) == -1) {
        fprintf(stderr, "listen error: %s\n", strerror(errno));
        exit(1);
    }
}

int mx_create_sockl(int port) {
    int sockl = socket(AF_INET, SOCK_STREAM, 0);
    int on = 0;
    struct sockaddr_in addr;

    if (sockl == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        exit(1);
    }
    if (ioctl(sockl, FIONBIO, (char *)&on) < 0) {
        perror("ioctl() failed");
        exit(1);
    }
    mx_set_sockaddr_any(&addr, port);
    if (bind(sockl, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "bind error: %s\n", strerror(errno));
        exit(1);
    }
    check_listen(sockl);
    return sockl;
}
