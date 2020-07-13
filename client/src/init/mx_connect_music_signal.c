#include "client.h"

void mx_music_signal_one(GtkWidget *send_play_btn, GtkWidget *stop_btn,
                         t_file *file, t_info *info) {
    g_object_set_data(G_OBJECT(send_play_btn), "name", 
                               file->msg_of_file->msg_f_name_of_file);
    g_signal_connect(G_OBJECT(send_play_btn), "clicked",
                              G_CALLBACK(mx_play_btn), (void *)info->music);
    g_object_set_data(G_OBJECT(stop_btn), "name", 
                               file->msg_of_file->msg_f_name_of_file);
    g_signal_connect(G_OBJECT(stop_btn), "clicked",
                              G_CALLBACK(mx_stop_btn), (void *)info->music);
}
