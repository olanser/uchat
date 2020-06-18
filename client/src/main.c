#include "client.h"

void mx_init_gtk() {
    mx_connect_builder();
    mx_connect_signals();
}

void mx_init() {
    mx_connect();
    mx_init_info();
    mx_init_gtk();
} 

void mx_show_window() {
    mx_show();
}

int main() {
    mx_init();
    mx_start_window();
}