#include "client.h"
#include "defines_client.h"

void mx_init_characters(t_info *info) {
    info->chars = malloc(sizeof(t_characters));
    info->chars->pacman = get_pacman(info);
}
