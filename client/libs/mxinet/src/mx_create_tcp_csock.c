#include "mxinet.h"

int mx_create_tcp_csock(int port, char* ip) {
    int sock = mx_create_sock(SOCK_STREAM);

    mx_connect_sock(sock, ip, port);
    return sock;
}
