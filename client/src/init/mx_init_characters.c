#include "client.h"
#include "defines_client.h"

static t_pacman *get_pacman(t_info *info) {
    t_pacman* pacman = malloc(sizeof(t_pacman));
    t_movable mov = {100, 100, 2, 0};
    const char *sprites[] = {MX_PAC_SP1, MX_PAC_SP2};

    pacman->draw_obj = mx_create_drobject(mov, sprites, 2, 
                                          MX_PACMAN_ANIM_DUR);
    mx_put_obj(GTK_LAYOUT(info->objs->chat_win->layout_main), 
               pacman->draw_obj);
    return pacman;
}

void mx_init_characters(t_info *info) {
    info->chars = malloc(sizeof(t_characters));
    info->chars->pacman = get_pacman(info);
}
