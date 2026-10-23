/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** server
*/

#ifndef SERVER_H
    #define SERVER_H

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <poll.h>
    #include <limits.h>
    #include <signal.h>

    #define MAX_CLIENTS 100
    #define BUFFER_SIZE 1024
    #define CMD_SIZE 1024
    #define PATH_MAX 4096
    #define MAX_USERNAME_LENGTH 1024

typedef struct client_s {
    int control_socket;
    int data_socket;
    char current_dir[PATH_MAX];
    char *server_root;
    int is_authenticated;
    int is_passive_mode;
    char username[MAX_USERNAME_LENGTH];
    int is_logged_with_user;
    char command_buffer[CMD_SIZE];
    struct sockaddr_in data_addr;
} client_t;

typedef struct {
    int server_socket;
    char root_path[PATH_MAX];
    struct pollfd fds[MAX_CLIENTS + 1];
    client_t clients[MAX_CLIENTS];
} server_t;

int init_server(server_t *server, int port, const char *path);
void run_server(server_t *server);
void cleanup_server(server_t *server);
void cleanup_client(server_t *server, int client_index);
int add_client(server_t *server, int client_socket);
void setup_signal_handler(void);
void handle_signal(int sig);

#endif
