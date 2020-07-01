#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sqlite3.h>
#include <stdbool.h>

#include "libmx.h"
#include "mxinet.h"

typedef struct s_server_users {
    int socket;
    int id_users;
    char *buff;
    bool work;
    pthread_mutex_t m_if_work;
    pthread_mutex_t m_write_socket;
}              t_server_users;

typedef struct s_user_in_chat {
    int usr_id;
    char *usr_nickname;
    struct s_user_in_chat *next;
}               t_user_in_chat;



typedef struct s_server {
    int size_connekt;
    pthread_mutex_t m_edit_database;
    sqlite3 *db;
    pthread_mutex_t m_logfile;
    int fd_logfile;
    pthread_rwlock_t m_edit_users;
    t_server_users *table_users;
    struct pollfd *poll_set;
    pthread_mutex_t m_works;
    t_list *works;
    int count_thread;
    pthread_t *thread;
    bool compress_array;
}              t_server;

typedef struct s_table_user {
    char *first_name;
    char *second_name;
    char *nickname;
    char *pass;
    int id;
    char avatar;
}               t_table_user;



typedef struct s_file_message {
    char *id_query;
    char *id_message;
    char *id_chat;
    int file_type;
    char *true_name;
    char *unique_name;
    int size;
}               t_file_message;



t_server *mx_create_server(int max_connect, int fd_server, int count_thread);
void *mx_thread(void *data);
int mx_accept_new_connect(t_server *server_info, int max_connect);
int mx_new_data_to_socket(t_server *server_info, int id);
void mx_compress_array(t_server *server_info);
bool mx_check_not_work(t_server_users *user);
void mx_work_thread(t_server *server_info, t_server_users *user);
char *mx_do_request(t_server *server_info, t_server_users *user);
void mx_write_socket(t_server_users *user, char *response);

//function
char *mx_create_response(char id_request, int query, char status);
int mx_check_number(char *str, int len);
int mx_do_query(char *sql, int (*callback)(void*,int,char**,char**),
                void *param, t_server *server_info);
bool mx_check_user_in_chat(int id_chat, int id_user, t_server *server_info);
void mx_send_response_user(t_server *server_info, char *response, char *sql);
int mx_callback_count(void *data, int column, char **name, char **tabledata);
int mx_return_one_str(void *param, int column, char **data, char **names);
bool mx_check_id_message_in_user(int id_message, int id_chat,
    t_server *server_info, t_server_users *user);
bool mx_check_avatar(char avatar);
void mx_add_log(t_server *server_info, char *msg);
void mx_add_error_work_log(t_server *server_info, t_server_users *user,
                           char *msg);
char *mx_create_respons_error_and_log(t_server *server_info,
    t_server_users *user, char *msg, char status);

//API
char *mx_signup(t_server *server_info, t_server_users *user);
bool mx_is_allowed_name(char *str);
int mx_check_symbols(t_table_user *tuser);
void mx_update_user(t_table_user* tuser, t_server_users *user,
                    t_server *server_info);
char *mx_signin(t_server *server_info, t_server_users *user);
int mx_get_msg_login(char status, char *request, t_table_user *tuser,
                     char **response);
char *mx_send_message(t_server *server_info, t_server_users *user);
char *mx_edit_message(t_server *server_info, t_server_users *user);
char *mx_get_chat_info(t_server *server_info, t_server_users *user);
void mx_delete_chat_users(t_user_in_chat **list);
void mx_push_char_users(t_user_in_chat **list, char *user_id, char *usr_nick);
char *mx_get_chat_users(t_server *server_info, t_server_users *user);
char *mx_get_user_info(t_server *server_info, t_server_users *user);
char *mx_get_msgs_time(t_server *server_info, t_server_users *user);
char *mx_show_users(t_server *server_info, t_server_users *user);
char *mx_delete_msg(t_server *server_info, t_server_users *user);
char *mx_send_file(t_server *server_info, t_server_users *user);
char *mx_change_avatar(t_server *server_info, t_server_users *user);
char *mx_join_chat(t_server *server_info, t_server_users *user);
void mx_get_msg_response_10(char status, char *request, char **response);
char *mx_create_chat(t_server *server_info, t_server_users *user);
char *mx_create_dialog(t_server *server_info, t_server_users *user);
char *mx_leave_chat(t_server *server_info, t_server_users *user);
char *mx_create_unique_name(t_server *server_info, t_server_users *user);
char *mx_get_chats_info(t_server *server_info, t_server_users *user);
char *mx_get_chat_msg(t_server *server_info, t_server_users *user);
char *mx_end_of_file(t_server *server_info, t_server_users *user);



#endif
