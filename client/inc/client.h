#ifndef CLIENT_H
#define CLIENT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include "objects.h"

#include <stdbool.h>

#include "openssl/ssl.h"
#include "openssl/err.h"

// dirs
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "fmod.h"


char *get_text_of_textview(GtkWidget *text_view);
char *mx_get_path_to_sticker(int number);
bool mx_check_file_registration(t_info *info);
void mx_create_file_registration(char *login, char *password);
bool mx_is_chat_exist(char id, t_list* list_of_chats);
void mx_go_to_dialog(t_info*info, int user_id);
t_chat_info* mx_get_chat_info(t_list* list, int id_chat);
t_msg* mx_get_msg_by_id(t_list *list_msg, int msg_id);
t_msg* mx_find_msg(t_list *chat_list, int msg_id, int chat_id);
t_msg* mx_get_msg_from_resp(char *resp, t_info *info);
int mx_add_msg_to_list(t_list **list_, t_msg *msg);
void mx_add_msg_to_box(GtkWidget*listbox, GtkWidget*widget, int index);
const char *mx_get_path_to_ava(int number);
char *mx_show_file_dialog(t_info *info);
int mx_send_msg_(int socket, char *buff, int size, t_info *info);
int mx_tsend_msg_(int socket, char *abuff, int size, t_info *info);
t_file *mx_get_file_by_msg_id(t_list *list, int id);
GtkWidget* mx_get_sized_img(const char *path, int width, int height);
char *mx_hash(const char *pass, const char *log);
char *mx_get_pango_from_uchat(char *uchat_format);
t_tag* mx_create_tag(char *uchat_f, char *pango_f, int start, int end) ;
char *mx_str_insert(char *string, char *substr, int index_to);
void mx_write_theme(char *theme_path);
char *mx_insert_str_between3(int start, int end, char*str_f, char*substr_f);
void mx_set_adjustment_auto_down(GtkBuilder* builder);

void mx_init_signals();
gboolean mx_scene_cycle(void *data);
void mx_init(t_info **info, int argc, char **argv);
void mx_init_gtk(t_info* info);
int mx_chang_scene(t_info *info, int scene);
void mx_do_iteration(t_info* info);
void mx_show_window(t_info* info);
void mx_connect_signals(t_info* info);
void mx_connect(t_info *info, int argc, char **argv);
void mx_init_characters(t_info *info);

// init gtk
GtkWidget* mx_get_stickers_notebook(GtkBuilder *builder, t_info *info);
void mx_set_profile_window(t_info *info);
GtkWidget* mx_build_get(GtkBuilder *builder, char *name);
void mx_init_main_chat_win(GtkBuilder *builder, 
                           t_main_chat_window *main_chat, 
                           t_info *info);
void mx_init_profile(t_info *info);
t_user_info* mx_crete_user(t_info* info);
void mx_init_objects(GtkBuilder *builder, t_objects *objs, t_info*info);
void mx_set_signin_win_properties(t_signin_window *signin);
void mx_set_signup_win_properties(t_signup_window *signup);
void mx_set_main_chat_properties(t_main_chat_window *main_chat);
void mx_set_properties(t_objects *objs);
void mx_connect_builder(t_info* info);
void mx_connect_css(void);
void mx_init_search_user(GtkBuilder *builder, 
                         t_main_chat_window *main_chat, t_info*info);
void mx_init_main_chat_win1(GtkBuilder *builder, 
                           t_main_chat_window *main_chat, 
                           t_info *info);
void mx_init_signup_win(GtkBuilder *builder, t_signup_window *signup);
void mx_init_signin_win(GtkBuilder *builder, t_signin_window *signin);

// api
int mx_api_delete_message(int id_msg, int id_chat, t_info *info);
int mx_api_edit_message(int id_chat, int id_msg, char *msg, t_info *info);
int mx_api_get_chat_info(int chat_id, t_info *info);
int mx_api_get_chat_users(int chat_id, t_info *info);
int mx_api_get_chats_info(t_info *info);
int mx_api_get_msgs_time(char *time, t_info *info);
int mx_api_get_user_info(int user_id, t_info *info);
int mx_api_send_message(int chat_id, char *msg, int type, t_info *info);
int mx_api_show_users(char *str, t_info *info);
int mx_api_signin(char **parameters, t_info *info);
int mx_api_signup(char **parameters, t_info *info);
int mx_api_get_chat_msgs(int id_chat, int last_msgs_id, 
                         int count, t_info *info);
int mx_api_create_dialog(int id_user, t_info *info);
int mx_api_get_unique_name_of_file(t_info *info);
int mx_api_end_send_file(void **parameters, t_info *info);
int mx_api_get_file(void **parameters, t_info *info);
int mx_api_change_avatar(int avatar, t_info *info);

// signals
void mx_btn_send_msg_clicked(GtkWidget* button, void* data);
void mx_btn_change_chat(GtkWidget* button, void* data);
gboolean mx_expand_focus_in(GtkWidget *widget, GdkEvent *event, void* data);
gboolean mx_expand_focus_out(GtkWidget *widget, GdkEvent *event, void* data);
void mx_expand_changed(GtkWidget *widget, void* data);
gboolean mx_expand_user_click(GtkWidget* widget, GdkEvent* event, void* data);
void mx_btn_del_msg(GtkWidget *button, GdkEvent*event, void *data);
void mx_btn_edit_msg(GtkButton *button, GdkEvent *event, void *data);
void mx_btn_choose_file(GtkWidget *button, t_info *info);
void mx_btn_show_stickers(GtkWidget* button, t_info* info);
void mx_btn_send_sticker(GtkWidget *button, GdkEvent*event, void *data);
void mx_btn_settings(GtkWidget *btn, t_info *info);
void mx_btn_exit(GtkButton *button, t_info *info);
void mx_btn_get_file(GtkButton *button, t_info *info);
void mx_btn_downloaded_click(GtkButton *button, void*data);
void mx_btn_change_avatar(GtkWidget *button, GdkEvent *event,  t_info *info);

//profile signals
void mx_btn_theme1(GtkWidget* button, t_info *info);
void mx_btn_theme2(GtkWidget* button, t_info *info);
void mx_btn_theme3(GtkWidget* button, t_info *info);
void mx_btn_theme4(GtkWidget* button, t_info *info);
void mx_btn_theme5(GtkWidget* button, t_info *info);
void mx_btn_save(GtkWidget* button, t_info *info);

void mx_play_btn(GtkButton *btn, void*data);
gboolean mx_scale_changed (GtkRange *range, GtkScrollType scroll,
                            gdouble value, void *user_data);
void mx_stop_btn(GtkButton *btn, void*data);
//signup
void mx_btn_signup(GtkWidget* button, void* data);
gboolean mx_key_press_signup(GtkWidget*widget, GdkEvent *event, t_info *info);
void mx_btn_go_to_signin(GtkWidget* widget, t_info *info);

// signin
gboolean mx_btn_signin(GtkButton *button, t_info *info);
gboolean mx_key_press_signin(GtkWidget*widget, GdkEvent *event, t_info *info);

//listener
void* mx_listener(void *data);
int mx_handle_response(t_info *info, char *response);

// handlers
int mx_h_who_is_that(char *response, t_info *info);
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
int mx_h_get_unique_name(char *response, t_info *info);

gboolean mx_handle_edit_msg(void* data);
gboolean mx_add_chat(void*data);
t_chat_info* mx_create_dialog_info(char* response, t_info *info, 
                                    GtkWidget *chat_widget);
int mx_handler_get_file(char *response, t_info *info);

//sendmsg
t_msg_widget* mx_get_msg_widget(char *response, t_info *info, t_msg* msg);
GtkWidget* mx_get_widget_of_file(t_file *file, t_info *info);
void mx_fill_msg_widget(char *response, t_info *info, t_msg_widget* msg_wid);
void mx_set_markup(GtkWidget *label, char *str);
GtkWidget *mx_sent_msg_build(char *response, 
                             t_msg_widget* msg_wid,
                             t_info *info);
char *mx_get_formated_substr(char *str, int *index, int *start_, int *end_);
bool mx_is_substr_valid(char *substr);
gboolean mx_handle_add_msg(void* data);

//signals_callback_func
gboolean mx_resize_signup_window (GtkWidget *window, t_objects *objs);
gboolean mx_resize_signin_window (GtkWidget *window, t_objects *objs);
gboolean mx_resize_main_window (GtkWidget *window, t_objects *objs);
gboolean mx_destroy_main_window(GtkWidget *window);
gboolean mx_destroy_signup_window(GtkWidget *window);
gboolean mx_destroy_signin_window(GtkWidget *window);
gboolean mx_go_fullscreen_signin_window(
    GtkWidget *window, GdkEventWindowState *event, t_objects *objs);
gboolean mx_vis_pass(GtkWidget *button, void *data);
gboolean mx_vis_pass_signin(GtkWidget *button, void *data);

// file_sender
void *mx_thread_send_file(void *data);
void mx_write_file(t_info *info);
void mx_free_file(t_file *file);

//music
t_fmod_info *mx_init_music();

#endif
