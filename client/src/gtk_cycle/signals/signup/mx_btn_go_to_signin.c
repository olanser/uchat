#include "client.h"
#include "defines_client.h"

void mx_btn_go_to_signin(GtkWidget* widget, t_info *info) {
    mx_chang_scene(info, MX_SCENE_SIGNIN);
}
