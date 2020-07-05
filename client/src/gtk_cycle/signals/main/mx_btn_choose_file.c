#include "client.h"

void mx_btn_choose_file(GtkWidget *button, t_info *info) {
    char *filename = mx_show_file_dialog(info);
    printf("filename = %s // mx_btn_choose_file\n", filename);
    
    free(filename);
}
