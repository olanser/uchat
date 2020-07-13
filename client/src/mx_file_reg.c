#include "client.h"
#include "mxinet.h"
#include "defines_client.h"

static bool check_buff(char *buff) {
    int i = 0;

    for (; buff[i] && i < 101; i++);
    if (i == 101)
        return true;
    while (buff[++i] == 0 && i < 101);
    if (i != 101)
        return true;
    while (buff[++i] != 0 && i < 202);
    if (i == 202)
        return true;
    while (buff[++i] == 0 && i < 202);
    if (i != 202)
        return true;
    return false;
}

void mx_set_theme(int fd) {
    char buff[1024];
    int count = read(fd, buff, 1024);
    GtkCssProvider *provider = gtk_css_provider_new();

    buff[count] = 0;
    gtk_css_provider_load_from_path(provider, buff, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
}

/* auto sigin 
*  if file valid = return true
*/
bool mx_check_file_registration(t_info *info) {
    int fd = open(MX_FILE_REG, O_RDONLY);
    int len;
    char buff[204];
    char *argv[2];

    if (fd == -1)
        return false;
    len = read(fd, buff, 202);
    if (len != 202 && check_buff(buff)) {
        close(fd);
        return false;
    }
    mx_set_theme(fd);
    close(fd);
    argv[0] = &buff[0];
    argv[1] = &buff[101];
    mx_api_signin(argv, info);
    return true;
}

/* create file and fill with buffer */
void mx_create_file_registration(char *login, char *password) {
    int fd = open(MX_FILE_REG, O_CREAT|O_WRONLY|O_TRUNC , S_IRWXU);
    char buff[300];

    memset(buff, 0, 202);
    if (fd == -1)
        return;
    if (login == 0 || password == 0) {
        close(fd);
        return;
    }
    memcpy(&buff[0], login, mx_strlen(login));
    memcpy(&buff[101], password, mx_strlen(password));
    write(fd, buff, 202);
    write(fd, MX_DIR_THEME1, 27);
    close(fd);
}
