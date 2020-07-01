#include "client.h"
#include "mxinet.h"

void mx_connect(t_info *info) {
    info->sock = mx_create_tcp_csock(2365, INADDR_LOOPBACK);
}
