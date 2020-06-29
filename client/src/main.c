  
#include "client.h"
#include "mxinet.h"
#include "defines.h"

static void reg(t_info *info) {
    // char *argv[4] = {"B", "b", "b", "b"};
    // mx_api_signup( argv,info);

    char *argv[2] = {"b", "b"};
    mx_api_signin( argv,info);
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
    // exit(0);
    mx_show_window(info);
}
