#include "libmx.h"

/*
* return count or -1 if no dir
*/
int mx_dirlen(char *rel_path) {
    DIR *dir = opendir(rel_path);
    struct dirent *ptr = 0;
    int len = 0;

    if (dir == 0)
        return -1;
    while((ptr = readdir(dir))) {
        len++;
    }
    closedir(dir);
    return len;
}