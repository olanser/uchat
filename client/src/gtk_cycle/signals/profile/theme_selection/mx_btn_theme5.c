#include "client.h"
#include "defines_client.h"

void mx_btn_theme5(GtkWidget* button, t_info *info) {
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(info->objs->s_win_profile->theme1_btn), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(info->objs->s_win_profile->theme2_btn), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(info->objs->s_win_profile->theme3_btn), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(info->objs->s_win_profile->theme4_btn), FALSE);
    gtk_css_provider_load_from_path(provider, MX_DIR_THEME5, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
    mx_write_theme(MX_DIR_THEME5);
}
