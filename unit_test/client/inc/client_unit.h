#ifndef CLIENT_UNIT
#define CLIENT_UNIT

#define MX_PORT 2365

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


typedef struct s_info {
    int socket;
} t_info;

#endif