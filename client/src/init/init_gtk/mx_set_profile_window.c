#include "client.h"
#include "defines_client.h"

GtkWidget* attach_img_at_pos(GtkGrid*grid, const char *path, int index, int w) {
    GtkWidget *ev_box = gtk_event_box_new();
    GtkWidget *image = mx_get_sized_img(path, 80, 80);
    int *avatar = malloc(sizeof(int));
    int x = index % w;
    int y = index / w;

    *avatar = index + 1;
    g_object_set_data(G_OBJECT(ev_box), "avatar", avatar);
    gtk_container_add(GTK_CONTAINER(ev_box), image);
    gtk_grid_attach(grid, ev_box, x, y, 1, 1);
    return ev_box;
}

void mx_set_profile_window(t_info *info) {
    char **mas = mx_get_dir_filenames(MX_DIR_AVATARS);
    int dirlen = mx_dirlen(MX_DIR_AVATARS);
    int i = 0;
    t_win_profile *prof = info->objs->s_win_profile;

    
    for (i = 0; i < dirlen - 3; i++) {
        GtkWidget * w = attach_img_at_pos(
            GTK_GRID(prof->grid_avatars), mx_get_path_to_ava(i + 1),
            i, dirlen - 3);
        g_signal_connect(G_OBJECT(w), "button-press-event", 
                         G_CALLBACK(mx_btn_change_avatar), info);
    }
    gtk_widget_show_all(prof->grid_avatars);
}