/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_psav
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

static void convert_ip_and_port(struct sockaddr_in *addr, client_t *client,
    char *response, size_t size)
{
    unsigned char *ip = (unsigned char *)&addr->sin_addr.s_addr;
    unsigned char *port = (unsigned char *)&client->data_addr.sin_port;

    snprintf(response, size,
        "Entering Passive Mode (%d,%d,%d,%d,%d,%d)",
        ip[0], ip[1], ip[2], ip[3], port[2], port[3]);
}

int handle_pasv(client_t *client, const char *arg)
{
    int data_sock;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char response[BUFFER_SIZE];

    (void)arg;
    data_sock = create_passive_socket(client);
    if (data_sock < 0) {
        send_response(client, FTP_ERROR_GENERIC,
            "Cannot create passive socket.");
        return -1;
    }
    getsockname(data_sock, (struct sockaddr *)&addr, &len);
    convert_ip_and_port(&addr, client, response, sizeof(response));
    client->data_socket = data_sock;
    client->is_passive_mode = 1;
    send_response(client, FTP_PASSIVE_MODE, response);
    return 0;
}
