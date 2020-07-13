#include "client.h"
#include "defines_client.h"
#include "icons.h"

static void set_lbl(GtkBuilder *builder, char *response, t_info *info) {
    GtkWidget *time_lbl = 0;
    GtkWidget *msg_bbl = 0;

    time_lbl = mx_build_get(builder, "rec_time_lbl");
    gtk_label_set_text(GTK_LABEL(time_lbl), &response[21]);
    gtk_widget_set_name(GTK_WIDGET (time_lbl), "time_lbl");
    msg_bbl = mx_build_get(builder, "rec_msg_tail_img");
    gtk_image_set_from_file(
        GTK_IMAGE (msg_bbl), "client/res/imgs/rec_msg_tail.png");
}

static GtkWidget *received_msg_build(char *response, t_msg_widget* msg_wid, t_info *info) {
    GtkBuilder *builder = gtk_builder_new_from_file("client/templates/message_box.xml");
    GtkWidget *msg_box = 0;
    GtkWidget *avatar = 0;
    GtkWidget *label = 0;
    GtkWidget *box = mx_build_get(builder, "rec_mainbox");

    msg_box = mx_build_get(builder, "rec_msg_lbl");
    gtk_widget_set_name(msg_box, MX_CSS_OTHER_MSG);
    avatar = mx_build_get(builder, "rec_avatar");
    gtk_image_set_from_file(
        GTK_IMAGE (avatar), mx_get_path_to_ava(response[41]));
    label = mx_build_get(builder, "rec_msg_lbl");
    gtk_label_set_label(GTK_LABEL (label), &response[46]);
    gtk_label_set_line_wrap(GTK_LABEL (label), TRUE);
    set_lbl(builder, response, info);
    msg_wid->label = label;
    return box;
}

void mx_fill_msg_widget(char *response, t_info *info, t_msg_widget* msg_wid) {
    GtkWidget *mainbox;

    if (*(int*)&response[17] == info->user_info->id) { // our msg
        mainbox = mx_sent_msg_build(response, msg_wid, info);
    }
    else{ // not our msg
        mainbox = received_msg_build(response, msg_wid, info);
    }
    gtk_widget_show_all(mainbox);
    msg_wid->widget = mainbox;
}
