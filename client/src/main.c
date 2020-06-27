  
#include "client.h"
#include "mxinet.h"
#include "defines.h"

int main(int argc, char *argv[]) {
    t_info *info = 0;
    gtk_init(&argc, &argv);
    mx_init(&info);
    mx_show_window(info);
    gtk_main();
    // system("leaks client");
    // mx_show_window(info);
}
