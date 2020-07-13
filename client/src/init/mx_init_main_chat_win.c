#include "client.h"
#include "defines_client.h"

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
