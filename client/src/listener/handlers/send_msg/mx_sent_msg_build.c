#include "client.h"
#include "defines_client.h"

static void set_edit_btn(char *response, t_info *info, GtkBuilder* builder) {
    GtkWidget *edit_button = (GtkWidget *)malloc(sizeof(GtkWidget));
    GtkWidget *img = (GtkWidget *)malloc(sizeof(GtkWidget));
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(
        MX_EDIT_MSG_BTN, 25, 25, NULL);
    int* id_msg = malloc(sizeof(int));

    *id_msg = *(int*)&response[9];
    edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "edit_btn"));
    img = GTK_WIDGET(gtk_builder_get_object(builder, "edit_img"));
    gtk_image_set_from_pixbuf(GTK_IMAGE (img), pixbuf);
    g_object_set_data(G_OBJECT(edit_button), "id_msg", id_msg);
    g_signal_connect(G_OBJECT(edit_button), "button-press-event",
                     G_CALLBACK(mx_btn_edit_msg), info);
}

static void set_del_btn(char *response, t_info *info, GtkBuilder* builder) {
    GtkWidget *del_button = (GtkWidget *)malloc(sizeof(GtkWidget));
    GtkWidget *img = (GtkWidget *)malloc(sizeof(GtkWidget));
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(
        MX_DEL_MSG_BTN, 25, 25, NULL);
    int* id_msg = malloc(sizeof(int));

    *id_msg = *(int*)&response[9];
    del_button = GTK_WIDGET(gtk_builder_get_object(builder, "del_btn"));
    img = GTK_WIDGET(gtk_builder_get_object(builder, "del_img"));
    gtk_image_set_from_pixbuf(GTK_IMAGE (img), pixbuf);
    g_object_set_data(G_OBJECT(del_button), "id_msg", id_msg);
    g_signal_connect(G_OBJECT(del_button), "button-press-event",
                     G_CALLBACK(mx_btn_del_msg), info);
}

static void mx_set1(GtkBuilder *builder, char *response) {
    GtkWidget *msg_box = 0;
    GtkWidget *avatar = 0;
    GtkWidget *msg_bbl = 0;
    GtkWidget *time_lbl = 0;

    msg_bbl = mx_build_get(builder, "send_msg_tail_img");
    gtk_image_set_from_file(GTK_IMAGE (msg_bbl), 
                            "client/res/imgs/send_msg_tail.png");
    msg_box = mx_build_get(builder, "send_msg_lbl");
    gtk_widget_set_name(msg_box, MX_CSS_OUR_MSG_BOX);
    avatar = mx_build_get(builder, "send_avatar");
    gtk_widget_set_name(GTK_WIDGET (avatar), "avatar");
    gtk_image_set_from_file(GTK_IMAGE (avatar), 
                            mx_get_path_to_ava(response[41]));
    time_lbl = mx_build_get(builder, "send_time_lbl");
    gtk_label_set_text(GTK_LABEL(time_lbl), &response[21]);
    gtk_widget_set_name(GTK_WIDGET (time_lbl), "time_lbl");
}

static void set_button_name(GtkBuilder *builder) {
    GtkWidget *del_button = 0;
    GtkWidget *edit_button = 0;

    del_button = mx_build_get(builder, "del_btn");
    gtk_widget_set_name(GTK_WIDGET(del_button), "del_btn");
    edit_button = mx_build_get(builder, "edit_btn");
    gtk_widget_set_name(GTK_WIDGET(edit_button), "edit_btn");
}

GtkWidget *mx_sent_msg_build(char *response, 
                             t_msg_widget* msg_wid,
                             t_info *info) {
    GtkBuilder *builder = gtk_builder_new_from_file(
        "client/templates/message_box.xml");
    GtkWidget *box = 0;
    GtkWidget *label = 0;

    mx_set1(builder, response);
    box = mx_build_get(builder, "send_mainbox");
    label = mx_build_get(builder, "send_msg_lbl");
    mx_set_markup(label, &response[46]);
    gtk_label_set_line_wrap(GTK_LABEL (label), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL (label), 5);
    set_button_name(builder);
    set_del_btn(response, info, builder);
    set_edit_btn(response, info, builder);
    msg_wid->label = label;
    return box;
}
