  
#include "client.h"
#include "mxinet.h"
#include "defines.h"

static void reg(t_info *info) {
    char *argv[2] = {"a", "a"};
    mx_api_signin( argv,info);
}

int main(int argc, char *argv[]) {
    t_info *info = 0;
    gtk_init(&argc, &argv);
    mx_init(&info);
    
    reg(info); // registration just for testing
    // exit(0);
    mx_show_window(info);
}
