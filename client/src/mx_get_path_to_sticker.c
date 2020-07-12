#include "client.h"
#include "defines_client.h"

char *mx_get_path_to_sticker(int number) {
    static const char *mas[] = {
        "client/res/stickers/pacman.png"
    };

    if (number > MX_MAX_SICKER) {
        return mx_strdup(mas[number]);
    }
    return mx_strdup(mas[number]);
}
