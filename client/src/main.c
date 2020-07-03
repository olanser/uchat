  
#include "client.h"
#include "mxinet.h"
#include "defines.h"

static void reg(t_info *info) {
    // if (mx_check_file_registration(info)) {
        char ch[] = "k";
        char *argv[4] = {ch, ch, ch, ch};
        mx_api_signup( argv,info);

    // char *argv[2] = {ch, ch};
    // mx_api_signin( argv,info);
    // }
}

static void wait_for_reg(t_info*info) {
    while(info->user_info != 0) { 
        usleep(1000);
    }
}

int main(int argc, char *argv[]) {
    t_info *info = 0;
    gtk_init(&argc, &argv);
    mx_init(&info);

    reg(info); // registration just for testing
    wait_for_reg(info);

    mx_api_get_chats_info(info);
    mx_api_get_chat_msgs(info->id_chat, 0, 10, info);
    // gdk_threads_add_timeout(33, mx_scene_cycle, info);
    // exit(0);
    // mx_show_window(info);
    gtk_main();
}
