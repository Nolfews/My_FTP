/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** server_run
*/

#include "../include/server.h"
#include "../include/response.h"
#include "../include/commands.h"
#include "errno.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

static ssize_t read_command(server_t *server, client_t *client,
    int client_index)
{
    char buffer[CMD_SIZE];
    ssize_t bytes_read =
        read(client->control_socket, buffer, sizeof(buffer) - 1);

    if (bytes_read <= 0) {
        cleanup_client(server, client_index);
        return -1;
    }
    buffer[bytes_read] = '\0';
    strncat(client->command_buffer, buffer,
        CMD_SIZE - strlen(client->command_buffer) - 1);
    return bytes_read;
}

static int setup_command(client_t *client, char *command, char *arg)
{
    char *crlf = strstr(client->command_buffer, "\r\n");
    size_t shift_size;
    size_t remaining;

    if (!crlf)
        crlf = strchr(client->command_buffer, '\n');
    if (!crlf)
        return 0;
    shift_size = (crlf[0] == '\r' && crlf[1] == '\n') ? 2 : 1;
    *crlf = '\0';
    command[0] = '\0';
    arg[0] = '\0';
    sscanf(client->command_buffer, "%31s %[^\n]", command, arg);
    remaining = strlen(crlf + shift_size);
    memmove(client->command_buffer, crlf + shift_size, remaining + 1);
    return 1;
}

static int handler_command(client_t *client, char *command, char *arg)
{
    command_handler_t *handler = find_command_handler(command);

    if (handler) {
        if (!client->is_authenticated &&
            strcmp(command, "USER") != 0 &&
            strcmp(command, "PASS") != 0 &&
            strcmp(command, "QUIT") != 0) {
            send_response(client, FTP_ERROR_NOT_LOGGED, "Please login first.");
            return 0;
        }
        return handler->handler(client, arg);
    } else {
        send_response(client, FTP_ERROR_SYNTAX, "Unknown command.");
        return 0;
    }
}

static int handle_client_command(server_t *server, int client_index)
{
    client_t *client = &server->clients[client_index];
    char command[32];
    char arg[CMD_SIZE];
    ssize_t bytes_read;
    int result;

    bytes_read = read_command(server, client, client_index);
    if (bytes_read <= 0)
        return -1;
    while (setup_command(client, command, arg)) {
        result = handler_command(client, command, arg);
        if (result == -2) {
            cleanup_client(server, client_index);
            return -1;
        }
    }
    return 0;
}

static int event_pool(server_t *server)
{
    int poll_count = poll(server->fds, MAX_CLIENTS + 1, -1);

    if (poll_count < 0) {
        if (errno == EINTR)
            return 0;
        perror("Poll failed");
        return -1;
    }
    return 0;
}

static void check_socket(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char client_ip[INET_ADDRSTRLEN];
    int new_socket;

    new_socket = accept(server->server_socket, (struct sockaddr *)&client_addr,
        &client_len);
    if (new_socket >= 0) {
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip,
            sizeof(client_ip));
        printf("New client connection from %s:%d\n", client_ip,
            ntohs(client_addr.sin_port));
        if (add_client(server, new_socket) < 0) {
            printf("Cannot accept new client, maximum reached\n");
            close(new_socket);
        }
    }
}

static void check_client_socket(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->fds[i + 1].fd != -1 &&
            server->fds[i + 1].revents & POLLIN)
            handle_client_command(server, i);
    }
}

void run_server(server_t *server)
{
    printf("Server starting...\n");
    setup_signal_handler();
    while (1) {
        if (event_pool(server) == -1)
            break;
        if (server->fds[0].revents & POLLIN) {
            check_socket(server);
        }
        check_client_socket(server);
    }
    printf("Fermeture du serveur...\n");
    cleanup_server(server);
    printf("Serveur arrêté proprement.\n");
}
