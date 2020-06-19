#include "client.h"

void mx_init_info(t_info **info) {
    *info = malloc(sizeof(t_info));
    (*info)->sock = 0;
}

void mx_connect(t_info *info) {
    info->sock = s
}

void mx_init_gtk() {
    mx_connect_builder();
    mx_connect_signals();
}

void mx_init(t_info **info) {
    mx_init_info(info);
    mx_connect(info);
    mx_init_gtk();
} 

void mx_show_window() {
    mx_show();
}

int main() {
    t_info *info = 0;
    mx_init(&info);
    mx_start_window();
}