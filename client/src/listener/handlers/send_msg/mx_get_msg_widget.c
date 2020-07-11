#include "client.h"
#include "icons.h"
#include "defines_client.h"

// static void set_edit_btn(char *response, t_info *info, GtkBuilder* builder) {
//     GtkWidget *edit_button = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *img = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(MX_EDIT_MSG_BTN, 10, 10, NULL);
//     int* id_msg = malloc(sizeof(int));

//     *id_msg = *(int*)&response[9];
//     edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "edit_btn"));
//     img = GTK_WIDGET(gtk_builder_get_object(builder, "edit_img"));
//     gtk_image_set_from_pixbuf(GTK_IMAGE (img), pixbuf);
//     g_object_set_data(G_OBJECT(edit_button), "id_msg", id_msg);
//     g_signal_connect(G_OBJECT(edit_button), "button-press-event", G_CALLBACK(mx_btn_edit_msg), info);
// }

// static void set_del_btn(char *response, t_info *info, GtkBuilder* builder) {
//     GtkWidget *del_button = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *img = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(MX_DEL_MSG_BTN, 10, 10, NULL);
//     int* id_msg = malloc(sizeof(int));

//     *id_msg = *(int*)&response[9];
//     del_button = GTK_WIDGET(gtk_builder_get_object(builder, "del_btn"));
//     img = GTK_WIDGET(gtk_builder_get_object(builder, "del_img"));
//     gtk_image_set_from_pixbuf(GTK_IMAGE (img), pixbuf);
//     g_object_set_data(G_OBJECT(del_button), "id_msg", id_msg);
//     g_signal_connect(G_OBJECT(del_button), "button-press-event", G_CALLBACK(mx_btn_del_msg), info);
// }

// static GtkWidget *sent_msg_build(char *response, t_msg_widget* msg_wid, t_info *info) {
//     GtkBuilder *builder = gtk_builder_new_from_file("templates/message_box.xml");
//     GtkWidget *box = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *msg_box = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *avatar = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *label = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *del_button = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *edit_button = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *msg_bbl = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *time_lbl = (GtkWidget *)malloc(sizeof(GtkWidget));

//     box = GTK_WIDGET(gtk_builder_get_object(builder, "send_mainbox"));
//     msg_bbl = GTK_WIDGET(gtk_builder_get_object(builder, "send_msg_tail_img"));
//     gtk_image_set_from_file(GTK_IMAGE (msg_bbl), "res/imgs/send_msg_tail.png");
//     msg_box = GTK_WIDGET(gtk_builder_get_object(builder, "send_msg_lbl"));
//     gtk_widget_set_name(msg_box, MX_CSS_OUR_MSG_BOX);
//     avatar = GTK_WIDGET(gtk_builder_get_object(builder, "send_avatar"));
//     gtk_widget_set_name(GTK_WIDGET (avatar), "avatar");
//     gtk_image_set_from_file(GTK_IMAGE (avatar), mx_get_path_to_ava(response[41]));
//     label = GTK_WIDGET(gtk_builder_get_object(builder, "send_msg_lbl"));
//     gtk_label_set_label(GTK_LABEL (label), &response[46]);
//     gtk_label_set_line_wrap(GTK_LABEL (label), TRUE);
//     gtk_label_set_max_width_chars(GTK_LABEL (label), 5);
//     time_lbl = GTK_WIDGET(gtk_builder_get_object(builder, "send_time_lbl"));
//     //HERE SET THE TIME//
//     gtk_widget_set_name(GTK_WIDGET (time_lbl), "time_lbl");
//     del_button = GTK_WIDGET(gtk_builder_get_object(builder, "del_btn"));
//     gtk_widget_set_name(GTK_WIDGET (del_button), "del_btn");
//     edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "edit_btn"));
//     gtk_widget_set_name(GTK_WIDGET (del_button), "del_btn");
//     set_del_btn(response, info, builder);
//     set_edit_btn(response, info, builder);
//     msg_wid->label = label;
//     return box;
// }

// static GtkWidget *received_msg_build(char *response, t_msg_widget* msg_wid, t_info *info) {
//     GtkBuilder *builder = gtk_builder_new_from_file("templates/message_box.xml");
//     GtkWidget *box = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *msg_box = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *avatar = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *label = (GtkWidget *)malloc(sizeof(GtkWidget));
//     GtkWidget *msg_bbl = (GtkWidget *)malloc(sizeof(GtkWidget));

//     box = GTK_WIDGET(gtk_builder_get_object(builder, "rec_mainbox"));
//     msg_bbl = GTK_WIDGET(gtk_builder_get_object(builder, "rec_msg_tail_img"));
//     gtk_image_set_from_file(GTK_IMAGE (msg_bbl), "res/imgs/rec_msg_tail.png");
//     msg_box = GTK_WIDGET(gtk_builder_get_object(builder, "rec_msg_lbl"));
//     gtk_widget_set_name(msg_box, MX_CSS_OTHER_MSG);
//     avatar = GTK_WIDGET(gtk_builder_get_object(builder, "rec_avatar"));
//     gtk_image_set_from_file(GTK_IMAGE (avatar), mx_get_path_to_ava(response[41]));
//     label = GTK_WIDGET(gtk_builder_get_object(builder, "rec_msg_lbl"));
//     gtk_label_set_label(GTK_LABEL (label), &response[46]);
//     gtk_label_set_line_wrap(GTK_LABEL (label), TRUE);
//     // gtk_label_set_max_width_chars(GTK_LABEL (label), 75);
//     msg_wid->label = label;
//     return box;
// }

// static void fill_msg_widget(char *response, t_info *info, t_msg_widget* msg_wid) {
//     GtkWidget *mainbox;

//     fprintf(stdout, "IM HERE\n");
//     if (*(int*)&response[17] == info->user_info->id) { // our msg
//         mainbox = sent_msg_build(response, msg_wid, info);
//     }
//     else{ // not our msg
//         mainbox = received_msg_build(response, msg_wid, info);
//     }
//     gtk_widget_show_all(mainbox);
//     msg_wid->widget = mainbox;
// }

static void fill_sticker_widget(char *response, t_info *info, t_msg_widget* msg_wid) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(&response[46], 100, 100, 0);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    GtkWidget *avatar = gtk_image_new_from_file(mx_get_path_to_ava(response[41]));

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

static void fill_file_widget(char *response, t_info *info, t_msg_widget* msg_wid, t_msg *msg) {
    msg_wid->widget = gtk_button_new_with_label(&response[46]);
    g_object_set_data(G_OBJECT(msg_wid->widget), "msg", msg);

    g_signal_connect(G_OBJECT(msg_wid->widget), "clicked", G_CALLBACK(mx_btn_get_file), info);
    gtk_widget_show(msg_wid->widget);
}

t_msg_widget* mx_get_msg_widget(char *response, t_info *info, t_msg* msg) {
    t_msg_widget *msg_widget = malloc(sizeof(t_msg_widget));

    printf("GET MSG WIDGET\n");
    if (*(int*)&response[42] == 1) {
        printf("MSG\n");
        mx_fill_msg_widget(response, info, msg_widget);
    }
    else if (*(int*)&response[42] == 2) {
        printf("STICKER\n");
        fill_sticker_widget(response, info, msg_widget);
    }
    else if (*(int*)&response[42] == 3) {
        printf("FILE\n");
        fill_file_widget(response, info, msg_widget, msg);
    }
        
    else {
        msg_widget->widget = gtk_label_new("UNDEFINED TYPE OF MSG");
        gtk_widget_show(msg_widget->widget);
    }
        
        // fill_msg_widget(response, info, msg_widget);
    return msg_widget;
}
