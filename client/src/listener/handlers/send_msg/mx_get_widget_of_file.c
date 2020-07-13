/* 
* author vbalachevs
* get msg widgets for all types of files
*/
#include "client.h"
#include "defines_client.h"

static GtkWidget* get_img_widget(t_file *file) {
    GtkWidget *widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *avatar = gtk_image_new_from_file(mx_get_path_to_ava(
        file->msg_of_file->msg_avatar));
    GtkWidget *image = 0;
    char filepath[512];

    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, 
            file->msg_of_file->msg_f_name_of_file);
    image = mx_get_sized_img(filepath, 200, 200);
    gtk_box_pack_start(GTK_BOX(widget), avatar, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(widget), image, TRUE, TRUE, 10);
    gtk_widget_show_all(widget);
    return widget;
}

static GtkWidget* get_audio_widget(t_file *file, t_info *info) {
    GtkBuilder *builder = gtk_builder_new_from_file("client/templates/player_msg.xml");
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "send_audio_mainbox"));
    GtkWidget *send_play_btn = GTK_WIDGET(gtk_builder_get_object(builder, "send_play_btn"));
    GtkWidget *send_name_btn = mx_build_get(builder, "send_name_btn");
    GtkWidget *box_scale = GTK_WIDGET(gtk_builder_get_object(builder, "box_scale"));
    GtkWidget *scale = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    GtkWidget *stop_btn = GTK_WIDGET(gtk_builder_get_object(builder, "send_stop_btn"));

    printf("%s\n", file->msg_of_file->msg_f_name_of_file);
    gtk_label_set_text(GTK_LABEL(send_name_btn), file->msg_of_file->msg_f_name_of_file);
    gtk_widget_set_hexpand(scale, TRUE);
    gtk_container_add(GTK_CONTAINER(box_scale), scale);
    g_object_set_data(G_OBJECT(send_play_btn), "scale", scale);
    g_object_set_data(G_OBJECT(send_play_btn), "name", file->msg_of_file->msg_f_name_of_file);
    g_object_set_data(G_OBJECT(stop_btn), "name", file->msg_of_file->msg_f_name_of_file);
    g_object_set_data(G_OBJECT(scale), "name", file->msg_of_file->msg_f_name_of_file);
    //void arr[t_file *, t_info *] = {file, info};
    g_signal_connect(G_OBJECT (scale), "change-value",G_CALLBACK(mx_scale_changed), (void *)info->music);
    g_signal_connect(G_OBJECT (send_play_btn), "clicked",G_CALLBACK(mx_play_btn), (void *)info->music);
    g_signal_connect(G_OBJECT (stop_btn), "clicked",G_CALLBACK(mx_stop_btn), (void *)info->music);
    //free(info->music->sound_to_pay);


    gtk_widget_show_all(widget);
    return widget;
}

static GtkWidget* get_else_widget(t_file *file) {
    GtkWidget *widget = gtk_button_new_with_label(
        file->msg_of_file->msg_f_name_of_file);

    g_signal_connect(G_OBJECT(widget), "clicked", 
                     G_CALLBACK(mx_btn_downloaded_click), 0);
    gtk_widget_show_all(widget);
    return widget;
}

GtkWidget* mx_get_widget_of_file(t_file *file, t_info *info) {
    GtkWidget *new_widget = 0;

    if (file->msg_of_file->msg_f_type == 1) {
        new_widget = get_img_widget(file);
    }
    else if (file->msg_of_file->msg_f_type == 4) {
        new_widget = get_audio_widget(file, info);
    }
    else
        new_widget = get_else_widget(file);
    return new_widget;
}
