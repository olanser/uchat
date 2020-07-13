#include "client.h"
#include "defines_client.h"

gboolean mx_vis_pass_signin(GtkWidget *button, void *data) {
    t_info *info = (t_info*) data;
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_size(MX_VISIBLE_ICON_W, 30, 30, NULL);
    GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file_at_size(MX_INVIS_ICON_W, 30, 30, NULL);

    if (!info->objs->s_signin_win->vis) {
        memset(&(info->objs->s_signin_win->vis), 1, sizeof(bool));
        gtk_entry_set_visibility(GTK_ENTRY (info->objs->s_signin_win->signin_password), TRUE);
        gtk_image_set_from_pixbuf(GTK_IMAGE (info->objs->s_signin_win->vis_img), pixbuf1);
    }
    else {
        memset(&(info->objs->s_signin_win->vis), 0, sizeof(bool));
        gtk_entry_set_visibility(GTK_ENTRY (info->objs->s_signin_win->signin_password), FALSE);
        gtk_entry_set_invisible_char (GTK_ENTRY (info->objs->s_signin_win->signin_password), 9679);
        gtk_image_set_from_pixbuf(GTK_IMAGE (info->objs->s_signin_win->vis_img), pixbuf2);
    }
    return true;
}
