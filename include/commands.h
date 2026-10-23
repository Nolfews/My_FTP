/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** commands
*/

#ifndef COMMANDS_H
    #define COMMANDS_H

    #include "server.h"

    #define COMMAND_BUFFER_SIZE 1024

typedef struct {
    const char *name;
    int (*handler)(client_t *client, const char *arg);
} command_handler_t;

typedef struct {
    unsigned int h1;
    unsigned int h2;
    unsigned int h3;
    unsigned int h4;
    unsigned int p1;
    unsigned int p2;
} address_t;

int handle_user(client_t *client, const char *username);
int handle_pass(client_t *client, const char *password);
int handle_pwd(client_t *client, const char *arg);
int handle_cwd(client_t *client, const char *path);
int handle_cdup(client_t *client, const char *arg);
int handle_pasv(client_t *client, const char *arg);
int handle_port(client_t *client, const char *arg);
int handle_list(client_t *client, const char *path);
int handle_retr(client_t *client, const char *filename);
int handle_stor(client_t *client, const char *filename);
int handle_dele(client_t *client, const char *filename);
int handle_help(client_t *client, const char *arg);
int handle_noop(client_t *client, const char *arg);
int handle_quit(client_t *client, const char *arg);

int create_passive_socket(client_t *client);
int establish_data_connection(client_t *client);
command_handler_t *find_command_handler(const char *command);

#endif
