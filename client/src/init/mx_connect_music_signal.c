#include "client.h"
#include "defines_client.h"

void mx_music_signal_one(GtkWidget *send_play_btn, GtkWidget *stop_btn,
                         t_file *file, t_info *info) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(MX_PLAY_BTN, 25,
                                                        25, NULL);
    GtkWidget *img = gtk_image_new_from_pixbuf(pixbuf);
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_size(MX_STOP_BTN, 25,
                                                          25, NULL);
    GtkWidget *img1 = gtk_image_new_from_pixbuf(pixbuf1);

    gtk_button_set_image(GTK_BUTTON (send_play_btn), GTK_WIDGET (img));
    gtk_button_set_image(GTK_BUTTON (stop_btn), GTK_WIDGET (img1));
    g_object_set_data(G_OBJECT(send_play_btn), "name", 
                               file->msg_of_file->msg_f_name_of_file);
    g_signal_connect(G_OBJECT(send_play_btn), "clicked",
                              G_CALLBACK(mx_play_btn), (void *)info->music);
    g_object_set_data(G_OBJECT(stop_btn), "name", 
                               file->msg_of_file->msg_f_name_of_file);
    g_signal_connect(G_OBJECT(stop_btn), "clicked",
                              G_CALLBACK(mx_stop_btn), (void *)info->music);
}
