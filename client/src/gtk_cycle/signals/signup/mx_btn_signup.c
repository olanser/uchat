#include "client.h"

static bool check_valid(char** params) {
    if ((params[2][0] == '\0') || (params[3][0] == '\0')) {
        return false;
    }
    return true;
}

void mx_btn_signup(GtkWidget* button, void* data) {
    t_info *info = (t_info*) data;
    const char *pass1 = gtk_entry_get_text(
        GTK_ENTRY(info->objs->s_signup_win->signup_pass1));
    const char *pass2 = gtk_entry_get_text(
        GTK_ENTRY(info->objs->s_signup_win->signup_pass2));
    const char *login = gtk_entry_get_text(
        GTK_ENTRY(info->objs->s_signup_win->signup_login));
    const char *parameters[4] = {"firstName", "secondName", login, pass1};

    if (mx_strcmp(pass1, pass2) != 0) {
        return;
    }
    if (check_valid((char**)parameters) == false)
        return;
    mx_create_file_registration(0, 0);
    mx_create_file_registration((char*)login, (char*)pass1);
    mx_api_signup((char**)parameters, info);
}
