#include "icons.h"
#include "defines_client.h"
#include "client.h"
#include "libmx.h"

static char **inti_avatars() {
    char **mas = 0;
    char **mas_buff = mx_get_dir_filenames(MX_DIR_AVATARS);
    int dirlen = mx_dirlen(MX_DIR_AVATARS);
    int i = 1;

    mas = malloc(sizeof(char*) * (dirlen - 1));
    while (mas_buff[++i]) {
        mas[i - 2] = mx_strjoin(MX_DIR_AVATARS, mas_buff[i]);
    }
    mas[i - 2] = 0;
    mx_del_strarr(&mas_buff);
    return mas;
}

const char *mx_get_path_to_ava(int number) {
    static bool first = true;
    static char **mas = 0;
    static int dirlen = 0;

    if (first == true) {
        dirlen = mx_dirlen(MX_DIR_AVATARS);
        mas = inti_avatars();
        first = false;
    }
    number--;
    if (number > dirlen - 2 || number < 0) {
        return MX_AVA_ERR;
    }
    return mas[number];
}
