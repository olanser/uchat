  
#include "client.h"
#include "mxinet.h"
#include "defines.h"

static void reg(t_info *info) {
    // char *argv[4] = {"a", "a", "a", "a"};
    // mx_api_signup( argv,info);

    char *argv[2] = {"a", "a"};
    mx_api_signin( argv,info);
}

int main(int argc, char *argv[]) {
    t_info *info = 0;
    gtk_init(&argc, &argv);
    mx_init(&info);
    reg(info); // registration just for testing
    mx_api_get_chats_info(info);
    // exit(0);
    mx_show_window(info);
}
