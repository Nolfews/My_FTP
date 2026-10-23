/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** response
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/response.h"

void send_response(client_t *client, int code, const char *message)
{
    char response[BUFFER_SIZE];
    int len;

    len = snprintf(response, sizeof(response), "%d %s\r\n", code, message);
    if (client->control_socket != -1)
        write(client->control_socket, response, len);
}

void send_multiline_response(client_t *client, int code, const char **messages,
    int count)
{
    char response[BUFFER_SIZE];
    int len;

    for (int i = 0; i < count - 1; i++) {
        len = snprintf(response, sizeof(response), "%d-%s\r\n", code,
            messages[i]);
        if (client->control_socket != -1)
            write(client->control_socket, response, len);
    }
    len = snprintf(response, sizeof(response), "%d %s\r\n", code,
        messages[count - 1]);
    if (client->control_socket != -1)
        write(client->control_socket, response, len);
}
