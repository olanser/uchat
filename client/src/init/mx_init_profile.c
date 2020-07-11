#include "client.h"
#include "defines_client.h"

static void init_prof1(t_info *info, 
                       t_win_profile *prof, GtkBuilder *builder) {
    prof->box_profile = mx_build_get(builder, "box_profile");
    prof->theme1_btn = mx_build_get(builder, "theme1_btn");
    prof->theme2_btn = mx_build_get(builder, "theme2_btn");
    prof->theme3_btn = mx_build_get(builder, "theme3_btn");
    prof->theme4_btn = mx_build_get(builder, "theme4_btn");
    prof->theme5_btn = mx_build_get(builder, "theme5_btn");
    prof->save_btn = mx_build_get(builder, "save_btn");
    prof->ev_box_profile_img = mx_build_get(builder, "ev_box_profile_img");
    prof->profile_img = mx_build_get(builder, "profile_img");
    prof->grid_avatars = mx_build_get(builder, "grid_avatars");
    gtk_layout_put(
        GTK_LAYOUT(info->objs->chat_win->layout_main), 
        prof->box_profile,
        (MX_WIN_WIDTH / 2) - (MX_WIN_PROF_W / 2),
        (MX_WIN_HEIGHT / 2) - (MX_WIN_PROF_H / 2));
    gtk_widget_show_all(prof->box_profile);
}

void mx_init_profile(t_info *info) {
    GtkBuilder* builder = gtk_builder_new_from_file(MX_PATH_PROFILE);
    t_win_profile *prof = info->objs->s_win_profile;

    init_prof1(info, prof, builder);
    gtk_widget_hide(prof->box_profile);
    gtk_widget_set_size_request(prof->box_profile,
                                MX_WIN_PROF_W, MX_WIN_PROF_H);
    gtk_widget_set_name(prof->box_profile, "box_profile");
    g_signal_connect(G_OBJECT(prof->theme1_btn), "clicked",
                     G_CALLBACK(mx_btn_theme1), info);
    g_signal_connect(G_OBJECT(prof->theme2_btn), "clicked",
                     G_CALLBACK(mx_btn_theme2), info);
    g_signal_connect(G_OBJECT(prof->theme3_btn), "clicked",
                     G_CALLBACK(mx_btn_theme3), info);
    g_signal_connect(G_OBJECT(prof->theme4_btn), "clicked",
                     G_CALLBACK(mx_btn_theme4), info);
    g_signal_connect(G_OBJECT(prof->theme5_btn), "clicked",
                     G_CALLBACK(mx_btn_theme5), info);
    g_signal_connect(G_OBJECT(prof->save_btn), "clicked",
                     G_CALLBACK(mx_btn_save), info);
}
