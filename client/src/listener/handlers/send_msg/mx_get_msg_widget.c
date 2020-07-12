#include "client.h"
#include "icons.h"
#include "defines_client.h"

static void fill_sticker_widget(char *response, t_info *info,
                                t_msg_widget* msg_wid) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(
        &response[46], 100, 100, 0);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    GtkWidget *avatar = gtk_image_new_from_file(
        mx_get_path_to_ava(response[41]));

    gtk_box_pack_start(GTK_BOX(box), avatar, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 1);
    if (*(int*)&response[17] == info->user_info->id) { // our msg
        gtk_widget_set_name(box, "send_sticker_msg");
    }
    else{
        gtk_widget_set_name(box, "rec_sticker_msg");
    }
    gtk_widget_show_all(box);
    msg_wid->widget = box;
}

static void fill_file_widget(char *response,
                             t_info *info,
                             t_msg_widget* msg_wid,
                             t_msg *msg) {
    msg_wid->widget = gtk_button_new_with_label(&response[46]);
    g_object_set_data(G_OBJECT(msg_wid->widget), "msg", msg);
    g_signal_connect(G_OBJECT(msg_wid->widget), "clicked",
                     G_CALLBACK(mx_btn_get_file), info);
    gtk_widget_show(msg_wid->widget);
}

t_msg_widget* mx_get_msg_widget(char *response, t_info *info, t_msg* msg) {
    t_msg_widget *msg_widget = malloc(sizeof(t_msg_widget));

    if (*(int*)&response[42] == 1) {
        mx_fill_msg_widget(response, info, msg_widget);
    }
    else if (*(int*)&response[42] == 2) {
        fill_sticker_widget(response, info, msg_widget);
    }
    else if (*(int*)&response[42] == 3) {
        fill_file_widget(response, info, msg_widget, msg);
    }
    else {
        msg_widget->widget = gtk_label_new("UNDEFINED TYPE OF MSG");
        gtk_widget_show(msg_widget->widget);
    }
    return msg_widget;
}
