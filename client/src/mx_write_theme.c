#include "client.h"
#include "defines_client.h"

void mx_write_theme(char *theme_path) {
    int fd = open(MX_FILE_REG, O_RDWR | O_APPEND);

    ftruncate(fd, 202);
    write(fd, theme_path, mx_strlen(theme_path));
    close(fd);
}
