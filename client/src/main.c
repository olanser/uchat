  
#include "client.h"
#include "mxinet.h"
#include "defines_client.h"

static void reg(t_info *info) {
    if (!mx_check_file_registration(info)) {
        mx_chang_scene(info, MX_SCENE_SIGNUP);
    }
    else {
        mx_chang_scene(info, MX_SCENE_MAIN_CHAT);
    }
}

int main(int argc, char *argv[]) {
    t_info *info = 0;

    gtk_init(&argc, &argv);
    mx_init(&info);
    reg(info);
    gtk_main();
}
