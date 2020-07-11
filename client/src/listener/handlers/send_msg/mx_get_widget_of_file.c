/* 
* author vbalachevs
* get msg widgets for all types of files
*/
#include <client.h>
#include <defines_client.h>

static GtkWidget* get_img_widget(t_file *file) {
    GtkWidget *widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *avatar = gtk_image_new_from_file(mx_get_path_to_ava(file->msg_of_file->msg_avatar));
    GtkWidget *image = 0;
    char filepath[512];

    sprintf(filepath, "%s/%s", MX_DIR_DOWNLOAD, file->msg_of_file->msg_f_name_of_file);
    image = mx_get_sized_img(filepath, 200, 200);
    gtk_box_pack_start(GTK_BOX(widget), avatar, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(widget), image, TRUE, TRUE, 10);

    gtk_widget_show_all(widget);
    return widget;
}

static GtkWidget* get_audio_widget(t_file *file) {
    GtkWidget *widget = gtk_label_new("AUDIO");

    gtk_widget_show_all(widget);
    return widget;
}

static GtkWidget* get_else_widget(t_file *file) {
    GtkWidget *widget = gtk_button_new_with_label(file->msg_of_file->msg_f_name_of_file);

    g_signal_connect(G_OBJECT(widget), "clicked", G_CALLBACK(mx_btn_downloaded_click), 0);
    gtk_widget_show_all(widget);
    return widget;
}

GtkWidget* mx_get_widget_of_file(t_file *file) {
    GtkWidget *new_widget = 0;

    printf("FILE // mx_get_widget_of_file\n");
    if (file->msg_of_file->msg_f_type == 1) {
        new_widget = get_img_widget(file);
    }
    else if (file->msg_of_file->msg_f_type == 4) {
        new_widget = get_audio_widget(file);
    }
    else
        new_widget = get_else_widget(file);
    return new_widget;
}
