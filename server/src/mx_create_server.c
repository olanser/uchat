#include "server.h"
#include "defines.h"

static t_server *create_malloc(int max_connect, int count_thread) {
    t_server *server_info = malloc(sizeof(t_server));

    if (server_info == 0) {
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        exit(1);
    }
    server_info->poll_set = malloc(sizeof(struct pollfd) * max_connect);
    server_info->table_users = malloc(sizeof(t_server_users) * max_connect);
    server_info->thread = malloc(sizeof(pthread_t) * count_thread);
    server_info->compress_array = false;
    if (server_info->poll_set == 0 || server_info->table_users == 0
        || server_info->thread == 0) {
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        exit(1);
    }
    pthread_mutex_init(&(server_info->m_edit_database), NULL);
    pthread_rwlock_init(&(server_info->m_edit_users), NULL);
    pthread_mutex_init(&(server_info->m_works), NULL);
    server_info->count_thread = count_thread;
    return server_info;
}

static void set_signal_and_create_thread(t_server *server_info) {
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGPIPE);

    sigprocmask(SIG_BLOCK, &newmask, 0);
    for (int i = 0; i < server_info->count_thread; i++)
        pthread_create(&(server_info->thread[i]), 0, mx_thread, server_info);
}

static void open_db(t_server *server_info) {
    char *temp;
    int a;
    char *err;

    if (sqlite3_open(MX_DATABASE, &(server_info->db)) != SQLITE_OK) {
        fprintf(MX_ERROR_THREAD, "Cannot open database: %s\n",
                sqlite3_errmsg(server_info->db));
        sqlite3_close(server_info->db);
        exit(1);
    }
    temp = mx_file_to_str(MX_CREATE_DATABASE);
    if (temp) {
        a = sqlite3_exec(server_info->db, temp, 0, temp, &err);
        if (a != SQLITE_OK) {
            fprintf(MX_ERROR_THREAD, "error: database query: %s\n", err);
            sqlite3_free(err);
        }
        free(temp);
    }
}

static void open_log_file(t_server *server_info, int fd_server) {
    int fd = open(MX_LOG_FILE, O_RDWR | O_APPEND | O_CREAT , S_IRWXU);
    if (fd == -1) {
        printf("ERROR OPEN LOG FILE\n");
        exit(1);
    }
    mx_init_ssl(server_info);
    server_info->fd_logfile = fd;
    pthread_mutex_init(&(server_info->m_logfile), NULL);
    server_info->poll_set[0].fd = fd_server;
    server_info->table_users[0].socket = fd_server;
    mx_start_demon(server_info);
    mx_add_log(server_info, "Start server\n");
}

t_server *mx_create_server(int fd_server) {
    t_server *server_info = create_malloc(MX_MAX_CONNECT, MX_THREAD);

    server_info->size_connekt = 1;
    server_info->works = 0;
    for (int i = 0; i < MX_MAX_CONNECT; i++) {
        server_info->poll_set[i].fd = 0;
        server_info->poll_set[i].events = POLLIN;
        server_info->poll_set[i].revents = 0;
        server_info->table_users[i].id_users = 0;
        server_info->table_users[i].socket = 0;
        server_info->table_users[i].work = 0;
        pthread_mutex_init(&(server_info->table_users[i].m_write_socket), NULL);
        pthread_mutex_init(&(server_info->table_users[i].m_if_work), NULL);
    }
    open_log_file(server_info, fd_server);
    open_db(server_info);
    set_signal_and_create_thread(server_info);
    return server_info;
}
