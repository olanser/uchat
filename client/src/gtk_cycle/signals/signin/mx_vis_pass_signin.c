#include "client.h"
#include "defines_client.h"

static void set_vis(t_signin_window *signin, GdkPixbuf *pixbuf1) {
    memset(&(signin->vis), 1, sizeof(bool));
    gtk_entry_set_visibility(GTK_ENTRY (signin->signin_password), TRUE);
    gtk_image_set_from_pixbuf(GTK_IMAGE (signin->vis_img), pixbuf1);
}

static void set_invis(t_signin_window *signin, GdkPixbuf *pixbuf2) {
    memset(&(signin->vis), 0, sizeof(bool));
    gtk_entry_set_visibility(GTK_ENTRY (signin->signin_password), FALSE);
    gtk_entry_set_invisible_char (GTK_ENTRY (signin->signin_password), 9679);
    gtk_image_set_from_pixbuf(GTK_IMAGE (signin->vis_img), pixbuf2);
}

gboolean mx_vis_pass_signin(GtkWidget *button, void *data) {
    t_info *info = (t_info*) data;
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_size(
                            MX_VISIBLE_ICON_W, 30, 30, NULL);
    GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file_at_size(
                            MX_INVIS_ICON_W, 30, 30, NULL);

    if (!info->objs->s_signin_win->vis) {
        set_vis(info->objs->s_signin_win, pixbuf1);
    }
    else {
        set_invis(info->objs->s_signin_win, pixbuf1);
    }
    return true;
}
