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
    char *strs[4];
    char buff[1000];

    strs[0] = mx_strdup("name1");
    strs[1] = mx_strdup("name2");
    strs[2] = mx_strdup("nick4");
    strs[3] = mx_strdup("pass2");
    mx_api_signup(strs, info);
    read(info->sock, buff, 9);
    read(info->sock, &buff[9], *(int*)&buff[5]);
    free(strs[0]);
    free(strs[1]);
    // char str[] = "1";
    // sleep(1);
    // mx_api_get_chat_users(str, info);
    // memset(buff, 0, 1000);
    // read(info->sock, buff, 9);
    // printf("type1 = %d\n", buff[0]);
    // printf("size1 = %d\n", *(int*)&buff[5]);
    // read(info->sock, &buff[9], *(int*)&buff[5]);

    // // for (int i = 9 + 10; i < *(int*)&buff[5]; i += 72) {
    // //     printf("user id = %s\n", &buff[i]);
    // //     printf("nickname = %s\n", &buff[i + 11]);
    // // }

    // for (int i = 0; i < *(int*)&buff[5]; i++) {
    //     printf("[%d] = %c\n", i, buff[i]);
    // }
    
    sleep(1);
    // system("leaks client");
    // mx_show_window(info);
}
