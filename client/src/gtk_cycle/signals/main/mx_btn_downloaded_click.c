#include "client.h"
#include "defines_client.h"

void mx_btn_downloaded_click(GtkButton *button, void*data) {
    pid_t pid = fork();

    if (pid == -1)
        return ;
    if (pid == 0) {
        char *argv[] = {"open", MX_DIR_DOWNLOAD, 0};
        execvp("open", argv);
        exit(0);
    }
}