#include "client.h"
#include "mxinet.h"
#include "defines.h"

static bool check_buff(char *buff) {
    int i = 0;

    for (; buff[i] && i < 101; i++);
    if (i == 101)
        return true;
    while (buff[++i] == 0 && i < 101);
    if (i != 101)
        return true;
    while (buff[++i] != 0 && i < 202);
    if (i == 202)
        return true;
    while (buff[++i] == 0 && i < 202);
    if (i != 202)
        return true;
    return false;
}

bool mx_check_file_registration(t_info *info) {
    int fd = open(MX_FILE_REG, O_RDONLY);
    int len;
    char buff[204];
    char *argv[2];

    if (fd == -1)
        return true;
    len = read(fd, buff, 204);
    if (len != 202) {
        printf("ERROR FILE registration\n");
        return true;
    }
    close(fd);
    if (check_buff(buff))
        return true;
    argv[0] = &buff[0];
    argv[1] = &buff[101];
    mx_api_signin(argv, info);
    return false;
}

void mx_create_file_registration(char *buff, int len) {
    int fd = open(MX_FILE_REG, O_CREAT|O_WRONLY|O_TRUNC , S_IRWXU);

    if (fd == -1)
        return;
    write(fd, buff, len);
    close(fd);
}