#ifndef LIB_MXINET
#define LIB_MXINET

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <sys/ioctl.h>

void mx_set_sockaddr_any(struct sockaddr_in *addr, int port);
int mx_create_sockl(int port);

#endif
