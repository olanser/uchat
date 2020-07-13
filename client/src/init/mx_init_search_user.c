#include "client.h"
#include "defines_client.h"

static GtkWidget* get_user_widget() {
    GtkWidget *widget = gtk_event_box_new();
    GtkWidget *label = gtk_label_new(")");

    gtk_widget_set_name(widget, "search_user");
    gtk_container_add(GTK_CONTAINER(widget), label);
    gtk_widget_show(label);
    return widget;
}

void mx_init_main_chat_win1(GtkBuilder *builder, 
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

static void init_list_of_users(t_main_chat_window *main_chat, t_info *info) {
    for (int i = 0; i < 10; i++) {
        t_user_info* user_info = 0;

        main_chat->user_widgets[i] = get_user_widget();
        user_info = malloc(sizeof(t_user_info));
        user_info->id = 0;
        g_object_set_data(G_OBJECT(main_chat->user_widgets[i]),
                            "user_info", user_info);
        gtk_list_box_insert(GTK_LIST_BOX(main_chat->list_box_users),
                            main_chat->user_widgets[i], -1);
        g_signal_connect(
            GTK_WIDGET(main_chat->user_widgets[i]),
            "button-press-event", G_CALLBACK(mx_expand_user_click), info);
    }
}


void mx_init_search_user(GtkBuilder *builder, 
                         t_main_chat_window *main_chat, t_info*info) {
    main_chat->search_users = mx_build_get(builder, "search_users");
    main_chat->list_box_users = gtk_list_box_new();
    gtk_widget_set_name(GTK_WIDGET (main_chat->list_box_users),
                        "searchbox_bg");
    gtk_list_box_insert(GTK_LIST_BOX(main_chat->listbox_search),
                        main_chat->list_box_users, -1);
    main_chat->user_widgets = malloc(sizeof(GtkWidget*) * 10);
    init_list_of_users(main_chat, info);
    gtk_widget_hide(main_chat->list_box_users);
    gtk_widget_show(main_chat->search_users);
}