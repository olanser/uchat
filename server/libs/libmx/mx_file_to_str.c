#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    char *str = 0;
    int fd = open(filename, O_RDWR);
    int size = 0;
    int status = 0;

    if (fd == -1) {
        fprintf(stderr, "open error: %s\n", strerror(errno));
        return 0;
    }
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    str = malloc(size + 1);
    status = read(fd, str, size);
    str[size] = 0;
    if (status == -1)
        return 0;
    close(fd);
    return str;
}
