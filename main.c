/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** main
*/

#include "./include/server.h"
#include <stdio.h>
#include <stdlib.h>

static void print_usage(char *binary)
{
    printf("USAGE: %s port path\n\t", binary);
    printf("port is the port number on which the server socket listens\n\t");
    printf("path is the path to the home directory for the Anonymous user\n");
}

int main(int argc, char **argv)
{
    server_t server;
    int port;

    if (argc != 3) {
        print_usage(argv[0]);
        return 84;
    }
    port = atoi(argv[1]);
    if (init_server(&server, port, argv[2]) != 0)
        return 84;
    printf("Server initialized successfully\n");
    run_server(&server);
    return 0;
}
