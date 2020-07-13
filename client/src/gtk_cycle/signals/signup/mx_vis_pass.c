#include "client.h"
#include "defines_client.h"

static void set_vis(t_signup_window *signup, GdkPixbuf *pixbuf1) {
    memset(&(signup->vis), 1, sizeof(bool));
    gtk_entry_set_visibility(GTK_ENTRY (signup->signup_pass1), TRUE);
    gtk_entry_set_visibility(GTK_ENTRY (signup->signup_pass2), TRUE);
    gtk_image_set_from_pixbuf(GTK_IMAGE (signup->vis_img), pixbuf1);
}

static void set_invis(t_signup_window *signup, GdkPixbuf *pixbuf2) {
    memset(&(signup->vis), 0, sizeof(bool));
    gtk_entry_set_visibility(GTK_ENTRY (signup->signup_pass1), FALSE);
    gtk_entry_set_visibility(GTK_ENTRY (signup->signup_pass2), FALSE);
    gtk_entry_set_invisible_char (GTK_ENTRY (signup->signup_pass1), 9679);
    gtk_entry_set_invisible_char (GTK_ENTRY (signup->signup_pass2), 9679);
    gtk_image_set_from_pixbuf(GTK_IMAGE (signup->vis_img), pixbuf2);
}

gboolean mx_vis_pass(GtkWidget *button, void *data) {
    t_info *info = (t_info*) data;
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_size(
                                MX_VISIBLE_ICON_W, 30, 30, NULL);
    GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file_at_size(
                                MX_INVIS_ICON_W, 30, 30, NULL);

    if (!info->objs->s_signup_win->vis)
        set_vis(info->objs->s_signup_win, pixbuf1);
    else
        set_invis(info->objs->s_signup_win, pixbuf2);
    return true;
}
