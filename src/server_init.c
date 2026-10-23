/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../include/server.h"
#include "../include/response.h"

static int check_root_path(const char *path, server_t *server)
{
    if (realpath(path, server->root_path) == NULL) {
        fprintf(stderr, "Error: Invalid path %s\n", path);
        return -1;
    }
    return 0;
}

static int create_socket(server_t *server)
{
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_socket < 0) {
        perror("Error creating socket");
        return -1;
    }
    return 0;
}

static int set_socket_option(server_t *server)
{
    int opt = 1;

    if (setsockopt(server->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
        sizeof(opt)) < 0) {
        perror("Error setting socket options");
        close(server->server_socket);
        return -1;
    }
    return 0;
}

static int bind_socket(server_t *server, int port)
{
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server->server_socket, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server->server_socket);
        return -1;
    }
    return 0;
}

static int listen_connection(server_t *server)
{
    if (listen(server->server_socket, 5) < 0) {
        perror("Error listening on socket");
        close(server->server_socket);
        return -1;
    }
    return 0;
}

static void init_poll_and_client_struct(server_t *server)
{
    server->fds[0].fd = server->server_socket;
    server->fds[0].events = POLLIN;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->fds[i + 1].fd = -1;
        server->fds[i + 1].events = POLLIN;
        server->clients[i].control_socket = -1;
        server->clients[i].data_socket = -1;
        server->clients[i].is_authenticated = 0;
        server->clients[i].is_logged_with_user = 0;
        server->clients[i].username[0] = '\0';
        server->clients[i].is_passive_mode = 0;
        strcpy(server->clients[i].current_dir, server->root_path);
        server->clients[i].server_root = strdup(server->root_path);
    }
}

int init_server(server_t *server, int port, const char *path)
{
    if (check_root_path(path, server) == -1)
        return -1;
    if (create_socket(server) == -1)
        return -1;
    if (set_socket_option(server) == -1)
        return -1;
    if (bind_socket(server, port) == -1)
        return -1;
    if (listen_connection(server) == -1)
        return -1;
    init_poll_and_client_struct(server);
    printf("FTP server initialized on port %d\n", port);
    printf("Root directory: %s\n", server->root_path);
    return 0;
}

void cleanup_client(server_t *server, int client_index)
{
    if (server->clients[client_index].control_socket != -1) {
        close(server->clients[client_index].control_socket);
        server->fds[client_index + 1].fd = -1;
        server->clients[client_index].control_socket = -1;
    }
    if (server->clients[client_index].data_socket != -1) {
        close(server->clients[client_index].data_socket);
        server->clients[client_index].data_socket = -1;
    }
    server->clients[client_index].is_authenticated = 0;
    server->clients[client_index].is_passive_mode = 0;
    strcpy(server->clients[client_index].current_dir, server->root_path);
    free(server->clients[client_index].server_root);
    server->clients[client_index].server_root = NULL;
}

void cleanup_server(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->fds[i + 1].fd != -1)
            cleanup_client(server, i);
    }
    if (server->server_socket != -1) {
        close(server->server_socket);
        server->server_socket = -1;
    }
}

int add_client(server_t *server, int client_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].control_socket == -1) {
            server->clients[i].control_socket = client_socket;
            server->fds[i + 1].fd = client_socket;
            server->fds[i + 1].events = POLLIN;
            strcpy(server->clients[i].current_dir, server->root_path);
            send_response(&server->clients[i], FTP_READY_FOR_NEW_USER,
                "Welcome to MyFTP server");
            return i;
        }
    }
    return -1;
}
