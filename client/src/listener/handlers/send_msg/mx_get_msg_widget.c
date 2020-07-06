#include "client.h"
#include "icons.h"
#include "defines_client.h"

static void con_edit_btn(GtkWidget *edit_button, char *response, t_info *info) {
    int* id_msg = malloc(sizeof(int));
    *id_msg = *(int*)&response[9];

    g_object_set_data(G_OBJECT(edit_button), "id_msg", id_msg);
    g_signal_connect(G_OBJECT(edit_button), "clicked", G_CALLBACK(mx_btn_edit_msg), info);
}

static GtkWidget* get_del_btn(char *response, t_info *info) {
    GtkWidget *ev_box = gtk_event_box_new();
    GtkWidget *image = gtk_image_new_from_file (MX_ICON_DELETE);
    int* id_msg = malloc(sizeof(int));

    gtk_container_add(GTK_CONTAINER(ev_box), image);
    *id_msg = *(int*)&response[9];
    g_object_set_data(G_OBJECT(ev_box), "id_msg", id_msg);
    g_signal_connect(G_OBJECT(ev_box), "button-press-event", G_CALLBACK(mx_btn_del_msg), info);
    return ev_box;
}

static GtkWidget* get_edit_btn(char *response, t_info *info) {
    GtkWidget *ev_box = gtk_event_box_new();
    GtkWidget *image = gtk_image_new_from_file (MX_ICON_EDIT);
    int* id_msg = malloc(sizeof(int));

    gtk_container_add(GTK_CONTAINER(ev_box), image);
    *id_msg = *(int*)&response[9];
    g_object_set_data(G_OBJECT(ev_box), "id_msg", id_msg);
    g_signal_connect(G_OBJECT(ev_box), "button-press-event", G_CALLBACK(mx_btn_edit_msg), info);
    return ev_box;
}

static GtkWidget *get_right_box(char *response, t_info *info) {
    GtkWidget *rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *del_button = get_del_btn(response, info);
    GtkWidget *edit_button = get_edit_btn(response, info);

    gtk_box_pack_start(GTK_BOX(rigth_box), del_button, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(rigth_box), edit_button, TRUE, TRUE, 1);
    return rigth_box;
}


static void fill_msg_widget(char *response, t_info *info, t_msg_widget* msg_wid) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    GtkWidget *right_box = 0;
    GtkWidget *avatar = gtk_image_new_from_file(mx_get_path_to_ava(response[41] - 49));
    GtkWidget *middle_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *label = gtk_label_new(&response[46]);

    gtk_box_pack_start(GTK_BOX(middle_box), label, TRUE, TRUE, 1);

    // gtk_box_pack_start(GTK_BOX(middle_box), label, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(box), avatar, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(box), middle_box, TRUE, TRUE, 1);
    gtk_widget_set_hexpand(label, TRUE);
    if (*(int*)&response[17] == info->user_info->id) { // our msg
        right_box = get_right_box(response, info);
        gtk_box_pack_start(GTK_BOX(box), right_box, TRUE, TRUE, 1);
        gtk_widget_set_name(box, MX_CSS_OUR_MSG_BOX);
    }
    else{ // not our msg
        gtk_widget_set_name(box, MX_CSS_OTHER_MSG);
    }
    gtk_widget_show_all(box);
    msg_wid->label = label;
    msg_wid->widget = box;
}

static void fill_sticker_widget(char *response, t_info *info, t_msg_widget* msg_wid) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(&response[46], 100, 100, 0);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    GtkWidget *avatar = gtk_image_new_from_file(mx_get_path_to_ava(response[41] - 49));

    gtk_box_pack_start(GTK_BOX(box), avatar, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 1);

    if (*(int*)&response[17] == info->user_info->id) { // our msg
        gtk_widget_set_name(box, MX_CSS_OUR_MSG_BOX);
    }
    else{
        gtk_widget_set_name(box, MX_CSS_OTHER_MSG);
    }
    gtk_widget_show_all(box);
    msg_wid->widget = box;
}

t_msg_widget* mx_get_msg_widget(char *response, t_info *info) {
    t_msg_widget *msg_widget = malloc(sizeof(t_msg_widget));

    if (*(int*)&response[42] == 1)
        fill_msg_widget(response, info, msg_widget);
    else if (*(int*)&response[42] == 2)
        fill_sticker_widget(response, info, msg_widget);
    else {
        msg_widget->widget = gtk_label_new("UNDEFINED TYPE OF MSG");
        gtk_widget_show(msg_widget->widget);
    }
        
        // fill_msg_widget(response, info, msg_widget);
    return msg_widget;
}
