#include "client_unit.h"

static void set_sockaddr(struct sockaddr_in *addr, int port) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // inet_aton("63.161.169.137", &myaddr.sin_addr.s_addr);
}

int mx_create_sock(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        exit(1);
    }
    struct sockaddr_in addr;
    set_sockaddr(&addr, port);
    if (connect(sock, (struct sockaddr*)&addr,sizeof(addr)) == -1) {
        fprintf(stderr, "connect error: %s\n", strerror(errno));
        exit(1);
    }
    
    return sock;
}

t_info *mx_get_info() {
    t_info *info = malloc(sizeof(t_info));

    info->socket = mx_create_sock(MX_PORT);
    return info;
}

void mx_signin(t_info* info) {
    char buff[1024];

    memset(buff, 0, 211);
    buff[0] = 1;
    *(int*)&buff[5] = 211;
    sprintf(&buff[9], "%s", "asd");
    sprintf(&buff[110], "%s", "asd");
    write(info->socket, buff, 211);
}

void mx_sendmsg(t_info* info) {
    char buff[1024];

    memset(buff, 0, 30);
    buff[0] = 2;
    *(int*)&buff[5] = 30;
    buff[9] = '1'; //id_chat
    sprintf(&buff[20], "dawawdawd"); //data end \0;
    write(info->socket, buff, 30);
}

void mx_editmsg(t_info* info) {
    char buff[1024];

    memset(buff, 0, 41);
    buff[0] = 3;
    *(int*)&buff[5] = 41;
    buff[9] = '1'; //id_chat 
    buff[20] = '1'; //id_msg
    sprintf(&buff[31], "dawawdawd"); //data end \0;
    write(info->socket, buff, 41);
}



void mx_get_info_chat(t_info* info) {
    char buff[1024];

    memset(buff, 0, 20);
    buff[0] = 10;
    *(int*)&buff[5] = 20;
    buff[9] = '1'; //id_chat 
    write(info->socket, buff, 20);
}

void mx_get_chats_info(t_info* info) {
    char buff[1024];

    memset(buff, 0, 9);
    buff[0] = 17;
    *(int*)&buff[5] = 9;
    buff[9] = '1'; //id_chat 
    write(info->socket, buff, 9);
}

// int checking(char *respons) {
//     printf("Response = %s %s %s %s %s %s\n", &respons[9], &respons[20], &respons[31],
//             &respons[42], &respons[62], &respons[63]);
//     if (strcmp(&respons[20], "1") != 0)
//         return 1;
//     if (strcmp(&respons[31], "1") != 0)
//         return 1;
//     if (strcmp(&respons[62], "0dawawdawd") != 0)
//         return 1;
//     if (strcmp(&respons[63], "dawawdawd") != 0)
//         return 1;
//     return 0;
// }

// int mx_read(t_info* info) {
//     char buff[1024];
//     int a;
//     bool check = true;
//     while (check) {
//         read(info->socket, buff, 9);
//         printf("buff = %d size = %d\n", buff[0], *(int*)&buff[5]);
//         a = read(info->socket, &buff[9], *((int *)&buff[5]));
//         printf("size = %d\n", *(int*)&buff[5]);
//         if (a + 9 != *(int *)&buff[5]) {
//             printf("not size %d %d != %d\n", buff[0], a + 9, *((int *)&buff[5]));
//             return 1;
//         }
//         printf("BUFF = %d\n", buff[0]);
//         if (buff[0] == 2)
//             return checking(buff);
//     }
//     return 0;
// }

int main(int argc, char *argv[]) {
    t_info **box_info =  malloc(sizeof(t_info*) * 100);
    char buff[1024];
    int size = 100;

    for (int i = 0; i < size; i++) {
        box_info[i] = mx_get_info();
        mx_signin(box_info[i]);
    }
    for (int i = 0; i < size; i++) {
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (buff[9] != (char)200)
            return 1;
    }
    for (int i = 0; i < size; i++) {
        mx_get_chat_msg(box_info[i]);
    }
    for (int i = 0; i < size; i++) {
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (buff[9] != '2')
            return 1;
        if (!(strcmp(&buff[10],"1") == 0 || strcmp(&buff[10],"2") == 0))
            return 1;
        if (!(strcmp(&buff[21], "General") == 0 
            || strcmp(&buff[21], "test_room") == 0))
            return 1;
        printf("%s\n", &buff[21]);
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (buff[9] != '2')
            return 1;
        if (!(strcmp(&buff[10],"1") == 0 || strcmp(&buff[10],"2") == 0))
            return 1;
        if (!(strcmp(&buff[21], "General") == 0 
            || strcmp(&buff[21], "test_room") == 0))
            return 1;
        printf("%s\n", &buff[21]);
    }
    for (int i = 0; i < size; i++)
        close(box_info[i]->socket);
    printf("OK\n");
    // for (int i = 0; i < 100; i++) {
    //     read(box_info[i]->socket, buff, 1024);
    //     if (buff[9] != (char)200)
    //         return 1;
    // }
    // for (int i = 0; i < 100; i++)
    //     mx_sendmsg(box_info[i]);

    // mx_editmsg(box_info[0]);
    // mx_sendmsg(box_info[0]);
    // mx_sendmsg(box_info[1]);
    // mx_sendmsg(box_info[2]);
    // sleep(1);
    // for (int i = 0; i <100; i++) {
        // return mx_read(box_info[0]);
    // }

    // sleep(3);
    // t_info *info = mx_get_info();


    // sleep(10);
    // mx_init(info, &argc, &argv);
    // mx_signin(info);
    // mx_sendmsg(info);
    // mx_registration(info);
    // mx_main(info);
    return 0;
}
