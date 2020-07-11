#ifndef MXINET_H
#define MXINET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// functions declaration
int mx_create_sock(int type);
void mx_connect_sock(int sock, char* ip, unsigned int port);
int mx_create_tcp_csock(int port, char* ip);
int mx_send_msg(int socket, char *buff, int size);
int mx_tsend_msg(int socket, char *buff, int size);
int mx_readn_sock(int socket, char *response, int size);

#endif
