#ifndef LIBMX_H
#define LIBMX_H

typedef struct s_list {
    void *data;
    struct s_list *next;
}              t_list;

#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <pwd.h>
#include <termios.h>

char *mx_strjoin_len(char *s1, char *s2, unsigned int len);
int mx_strlen(const char *s);
void mx_str_reverse(char *s);
char *mx_strnew(const int size);
char *mx_strdup(const char *s1);
char *mx_strcpy(char *dst, const char *src);
char *mx_strndup(const char *s1, size_t n);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_strjoin2(char *s1, char *s2);
char *mx_strjoin3(char *s1, char *s2);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_front_free_data(t_list **head);
void mx_pop_back(t_list **head);

#endif
