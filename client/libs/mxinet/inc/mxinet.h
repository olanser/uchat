#ifndef MXINET_H
#define MXINET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

// functions declaration
int mx_create_sock(int type);
void mx_connect_sock(int sock, unsigned int ip, unsigned int port);

#endif 