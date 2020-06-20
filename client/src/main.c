#include "client.h"
#include "mxinet.h"
#include "defines.h"

int main(int argc, char *argv[]) {
    t_info *info = 0;
    gtk_init(&argc, &argv);
    mx_init(&info);
    gtk_main();
    // mx_show_window(info);
}