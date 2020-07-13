#include "client.h"

static bool check_valid(char** params) {
    if ((params[0][0] == '\0') || (params[1][0] == '\0')) {
        return false;
    }
    return true;
}

gboolean mx_btn_signin(GtkButton *button, t_info *info) {
    const char *login = gtk_entry_get_text(
        GTK_ENTRY(info->objs->s_signin_win->signin_login));
    const char *pass = gtk_entry_get_text(
        GTK_ENTRY(info->objs->s_signin_win->signin_password));
    const char *new_pass = mx_hash(pass, login);
    const char *parameters[2] = {login, new_pass};

    if (check_valid((char**)parameters) == false) {
        free((char*)new_pass);
        return true;
    }
    mx_create_file_registration(0, 0);
    mx_create_file_registration((char*)login, (char*)new_pass);
    mx_api_signin((char**)parameters, info);
    free((char*)new_pass);
    return TRUE;
}
