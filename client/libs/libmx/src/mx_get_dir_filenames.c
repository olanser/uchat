/* 
* author vbalachevs
*/
#include "libmx.h"
#include <errno.h>
#include <string.h>

/* Null ternimated allocated mas */
char **mx_get_dir_filenames(char *rel_path_to_dir) {
    DIR *dir = opendir(rel_path_to_dir);
    struct dirent *ptr = 0;
    char **strings = 0;
    int len = 0;
    int i = 0;

    if (dir == 0)
        return 0;
    len = mx_dirlen(rel_path_to_dir);
    strings = malloc(sizeof(char*) * (len+ 1));
    for (i = 0; i < len; i++) {
        ptr = readdir(dir);
        strings[i] = mx_strdup(ptr->d_name);
    }
    strings[i] = 0;
    closedir(dir);
    return strings;
}
