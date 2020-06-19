#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#ifdef __linux__
#include <sys/wait.h>
#endif
#include "defines.h"
#include "libmx.h"
#include <sys/stat.h>

typedef struct s_updates {
    t_list *list_head;
    t_list *list_id;
    char *time;
    sigset_t newmask;
}   t_updates;

typedef struct s_user {
    char *id; // -1 if no user
    char *username; // nickname
    int socket;
    pthread_mutex_t m_fd;
    t_updates *updates;
}   t_user;


typedef struct s_table_user {
    char *id;
    char *first_name;
    char *second_name;
    char *nickname;
    char *pass;
} t_table_user;

typedef struct s_table_message {
    char *id_query;
    char *id_message;
    char *id_chat;
    unsigned int size;
    char *data;
} t_table_message;

typedef struct s_file_message {
    char *id_query;
    char *id_message;
    char *id_chat;
    int file_type;
    char *true_name;
    char buf_name[15];
    int size;
} t_file_message;

typedef struct s_user_in_chat {
    char *usr_id;
    char *usr_nickname;
    struct s_user_in_chat *next;
}               t_user_in_chat;

// list
t_list *mx_create_node(void *data);
void mx_push_top(t_list **list, void *data);
void mx_pop_index(t_list **list, int index);

// serve 
void serve(int socket);
char mx_read_socket(int socket, char **request);
void mx_handle_out(int socket, int status, char **response);
int mx_handle_input(char *request, char **response, t_user *user_info);
int mx_do_query(char *sql, int (*callback)(void*,int,char**,char**), void* param);
void mx_free_tuser(t_table_user *tuser);
int mx_upd_pr_data(char* user_id);

// authenticate
int mx_authenticate(void *request, char **response, t_user *user_info);
//sendmessage
int mx_send_message(void *request, char **response, t_user *user_info);
int mx_check_message(char *request, t_table_message *message);
bool mx_check_user_in_char(char *id_chat, char *id_user);
void mx_create_signal_new_message(char *id_chat);
void mx_create_response(void *request, char **response);
int mx_check_number(char *str, int len);
//editmessage
int mx_editmessage(void *request, char **response, t_user *user_info);
//delete_msg
int mx_delete_msg(void *request, char **response, t_user *user_info);
//get_msgs_time
int mx_get_msgs_time(void *request, char **response, t_user *user_info);
// signin 
int mx_get_msg_login(char status, char *request, t_table_user *tuser, char **response);
int mx_signin(void *request, char **response, t_user *user_info);
bool mx_is_allowed_name(char *str) ;
int mx_signup(void *request, char **response, t_user *user);
int mx_check_symbols(t_table_user *tuser);
void mx_update_user(t_user* user);
//get_user_info
int mx_get_user_info(void *request, char **response, t_user *user_info);
//get_chat_info
int mx_get_msg_chat(char status, char *request, void *data, char **response);
int mx_get_chat_info(void *request, char **response, t_user *user_info);
//show_users
int mx_show_users(void *request, char **response, t_user *user_info);
//pthread
pthread_t mx_create_pthread_updates(t_user *user_info);
int mx_callback_updates(void *data, int columns, char **name, char **tabledata);
//get_chat_users
int mx_get_chat_users(void *request, char **response, t_user *user_info);
void mx_push_char_users(t_user_in_chat **list, char *user_id, char *usr_nick);
void mx_delete_chat_users(t_user_in_chat **list);
//join_chat
int mx_join_chat(void *request, char **response, t_user *user_info);
int mx_get_msg_response_10(char status, char *request, char **response);
//create_chat
int mx_create_chat(void *request, char **response, t_user *user_info);
// create_dialog
int mx_create_dialog(void *request, char **response, t_user *user_info);
//leave_chat
int mx_leave_chat(void *request, char **response, t_user *user_info);
//send_file
int mx_send_file(void *request, char **response, t_user *user_info);


#endif
