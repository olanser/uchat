#include "client.h"
#include "mxinet.h"
#include "defines.h"
#include "libmx.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
    t_info *info = 0;
    gtk_init(&argc, &argv);
    mx_init(&info);

    // system("leaks client");
    // mx_show_window(info);
}
