#include "mxinet.h"

int mx_create_sockl(int port) {
    int sockl = socket(AF_INET, SOCK_STREAM, 0);
    int on = 0;
    
    if (sockl == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        exit(1);
    }
    if (ioctl(sockl, FIONBIO, (char *)&on) < 0) {
        perror("ioctl() failed");
        //close(sockl);
        exit(1);
    }
    struct sockaddr_in addr;
    mx_set_sockaddr_any(&addr, port);
    if (bind(sockl, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "bind error: %s\n", strerror(errno));
        exit(1);
    }
    listen(sockl, SOMAXCONN);
    if (listen(sockl, SOMAXCONN) == -1) {
        fprintf(stderr, "listen error: %s\n", strerror(errno));
        exit(1);
    }
    return sockl;
}
