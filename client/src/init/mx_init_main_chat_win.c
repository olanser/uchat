#include "client.h"
#include "defines_client.h"

static GtkWidget* get_user_widget() {
    GtkWidget *widget = gtk_event_box_new();
    GtkWidget *label = gtk_label_new(")");

    gtk_container_add(GTK_CONTAINER(widget), label);
    gtk_widget_show(label);
    return widget;
}

static void set_icons(t_main_chat_window *main_chat, GtkBuilder *builder) {
    GdkPixbuf *pixbuf;

    main_chat->send_img = mx_build_get(builder, "image4");
    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_SEND_ICON_W, 30, 30, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE (main_chat->send_img), pixbuf);
    main_chat->exit_img = mx_build_get(builder, "image2");
    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_EXIT_ICON_W, 30, 30, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE (main_chat->exit_img), pixbuf);
    main_chat->settings_img = mx_build_get(builder, "image3");
    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_STNGS_ICON_W, 30, 30, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE (main_chat->settings_img), pixbuf);
    main_chat->new_chat_img = mx_build_get(builder, "image1");
    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_NEWCH_ICON_W, 30, 30, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE (main_chat->new_chat_img), pixbuf);
    main_chat->stickers_img = mx_build_get(builder, "image5");
    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_STICK_ICON_W, 30, 30, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE (main_chat->stickers_img), pixbuf);
    main_chat->attach_img = mx_build_get(builder, "image6");
    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_ATACH_ICON_W, 30, 30, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE (main_chat->attach_img), pixbuf);
}

static void mx_init_main_chat_win1(GtkBuilder *builder, 
                           t_main_chat_window *main_chat, 
                           t_info *info) {
    main_chat->chat_win = mx_build_get(builder, "main_chat_window1");
    if (main_chat->chat_win == 0)
        fprintf(stderr, "error of open file!\n"); 
    main_chat->layout_main = mx_build_get(builder, "layout_main");
    main_chat->main_chat_box = mx_build_get(builder, "main_chat_box1");
    main_chat->paned_chat = mx_build_get(builder, "paned_chat1");
    main_chat->btn_logout = mx_build_get(builder, "btn_logout");
    main_chat->selected_chat_lbl = mx_build_get(builder,
                                                "selected_chat_lbl1");
    main_chat->send_btn = mx_build_get(builder, "send_btn");
    main_chat->search_line = mx_build_get(builder, "search_line1");
    main_chat->profile_set_btn = mx_build_get(builder, "profile_set_btn1");
    main_chat->chat_line = mx_build_get(builder, "text_view_msg");
}

void mx_init_search_user(GtkBuilder *builder, 
                         t_main_chat_window *main_chat, t_info*info) {
    main_chat->search_users = mx_build_get(builder, "search_users");
    main_chat->list_box_users = gtk_list_box_new();
    gtk_list_box_insert(GTK_LIST_BOX(main_chat->listbox_search),
                        main_chat->list_box_users, -1);
    main_chat->user_widgets = malloc(sizeof(GtkWidget*) * 10);
    for (int i = 0; i < 10; i++) {
        main_chat->user_widgets[i] = get_user_widget();
        t_user_info* user_info = malloc(sizeof(t_user_info));
        user_info->id = 0;
        g_object_set_data(G_OBJECT(main_chat->user_widgets[i]),
                          "user_info", user_info);
        gtk_list_box_insert(GTK_LIST_BOX(main_chat->list_box_users),
                            main_chat->user_widgets[i], -1);
        g_signal_connect(
            GTK_WIDGET(main_chat->user_widgets[i]),
            "button-press-event", G_CALLBACK(mx_expand_user_click), info);
    }
    gtk_widget_hide(main_chat->list_box_users);
    gtk_widget_show(main_chat->search_users);
}

void mx_init_main_chat_win(GtkBuilder *builder, 
                           t_main_chat_window *main_chat, 
                           t_info *info) {
    mx_init_main_chat_win1(builder, main_chat, info);
    gtk_widget_set_name(GTK_WIDGET (main_chat->chat_line), "text_entry");
    main_chat->search_pan_main_box = mx_build_get(builder,
                                                  "search_pan_main_box");
    main_chat->chat_entry_split_box = mx_build_get(builder,
                                                   "chat_entry_split_box");
    main_chat->listbox_search = mx_build_get(builder, "listbox_search");
    gtk_widget_set_name(GTK_WIDGET (main_chat->listbox_search),
                        "search_panel");
    main_chat->search_viewport1 = mx_build_get(builder, "search_viewport1");
    main_chat->notebook = mx_build_get(builder, "notebook");
    main_chat->btn_choose_file = mx_build_get(builder, "btn_choose_file");
    main_chat->btn_show_sticker = mx_build_get(builder, "btn_show_sticker");
    main_chat->btn_settings = mx_build_get(builder, "btn_settings");
    set_icons(main_chat, builder);
    gtk_widget_show_all(main_chat->chat_win);
    main_chat->notebook_stickers = mx_get_stickers_notebook(builder, info);
    mx_init_search_user(builder, main_chat, info);
}
