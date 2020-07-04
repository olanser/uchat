#include "client.h"

void mx_btn_exit(GtkButton *button, GdkEvent *event, t_info *info) {
    mx_create_file_registration(0, 0);
    exit(0);
}
