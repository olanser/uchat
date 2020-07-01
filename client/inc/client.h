#ifndef CLIENT_H
#define CLIENT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include "objects.h"
#include <stdbool.h>

char *get_text_of_textview(GtkWidget *text_view);
char *mx_get_path_to_sticker(int number);
bool mx_check_file_registration(t_info *info);
void mx_create_file_registration(char *buff, int len);
bool mx_is_chat_exist(char id, t_list* list_of_chats);
void mx_go_to_dialog(t_info*info, int user_id);

gboolean mx_scene_cycle(void *data);
void mx_init(t_info **info);
void mx_init_gtk(t_info* info);
int mx_chang_scene(t_info *info, int scene);
void mx_do_iteration(t_info* info);
void mx_show_window(t_info* info);
void mx_connect_signals(t_info* info);
void mx_connect(t_info *info);

// api
int mx_api_delete_message(int id_msg, int id_chat, t_info *info);
int mx_api_edit_message(int id_chat, int id_msg, char *msg, t_info *info);
int mx_api_get_chat_info(int chat_id, t_info *info);
int mx_api_get_chat_users(int chat_id, t_info *info);
int mx_api_get_chats_info(t_info *info);
int mx_api_get_msgs_time(char *time, t_info *info);
int mx_api_get_user_info(int user_id, t_info *info);
int mx_api_send_message(int chat_id, char *msg, t_info *info);
int mx_api_show_users(char *str, t_info *info);
int mx_api_signin(char **parameters, t_info *info);
int mx_api_signup(char **parameters, t_info *info);
int mx_api_get_chat_msgs(int id_chat, int last_msgs_id, int count, t_info *info);
int mx_api_create_dialog(int id_user, t_info *info);

// signals
void mx_btn_send_msg_clicked(GtkWidget* button, void* data);
void mx_btn_change_chat(GtkWidget* button, void* data);
gboolean mx_expand_focus_in(GtkWidget *widget, GdkEvent *event, void* data);
gboolean mx_expand_focus_out(GtkWidget *widget, GdkEvent *event, void* data);
void mx_expand_changed(GtkWidget *widget, void* data);
gboolean mx_expand_user_click(GtkWidget* widget, GdkEvent* event, void* data);

//listener
void* mx_listener(void *data);
int mx_handle_response(t_info *info, char *response);

// handlers
int mx_h_authenticate(char *response, t_info *info);
int mx_h_authenticate(char *response, t_info* info);
int mx_h_create_chat(char *response, t_info* info);
int mx_h_create_dialog(char *response, t_info* info);
int mx_h_delete_msg(char *response, t_info* info);
int mx_h_edit_msg(char *response, t_info* info);
int mx_h_get_chat_info(char *response, t_info* info);
int mx_h_get_chat_users(char *response, t_info* info);
int mx_h_get_file(char *response, t_info* info);
int mx_h_get_msgs_time(char *response, t_info* info);
int mx_h_get_user_info(char *response, t_info* info);
int mx_h_join_chat(char *response, t_info* info);
int mx_h_leave_chat(char *response, t_info* info);
int mx_h_read_message(char *response, t_info* info);
int mx_h_send_file(char *response, t_info* info);
int mx_h_send_msg(char *response, t_info* info);
int mx_h_show_users(char *response, t_info* info);
int mx_h_signin(char *response, t_info* info);
int mx_h_signup(char *response, t_info* info);
int mx_h_get_chats_info(char *response, t_info *info);

//signals_callback_func
gboolean mx_resize_signup_window (GtkWidget *window, t_objects *objs);
gboolean mx_resize_signin_window (GtkWidget *window, t_objects *objs);
gboolean mx_resize_main_window (GtkWidget *window, t_objects *objs);
gboolean mx_destroy_main_window(GtkWidget *window);
gboolean mx_destroy_signup_window(GtkWidget *window);
gboolean mx_destroy_signin_window(GtkWidget *window);
gboolean mx_go_fullscreen_signin_window(GtkWidget *window, GdkEventWindowState *event, t_objects *objs);
//

#endif
