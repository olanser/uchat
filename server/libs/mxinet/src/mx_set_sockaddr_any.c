#include "mxinet.h"

void mx_set_sockaddr_any(struct sockaddr_in *addr, int port) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_aton("63.161.169.137", &myaddr.sin_addr.s_addr);
}
