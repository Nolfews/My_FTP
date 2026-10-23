/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_port
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <string.h>
#include <stdio.h>

static void make_adress(address_t *address, client_t *client)
{
    struct sockaddr_in *addr = &client->data_addr;

    memset(addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(address->p1 * 256 + address->p2);
    addr->sin_addr.s_addr = htonl((address->h1 << 24) | (address->h2 << 16) |
        (address->h3 << 8) | address->h4);
    client->is_passive_mode = 0;
}

int handle_port(client_t *client, const char *arg)
{
    address_t address;

    if (sscanf(arg, "%u,%u,%u,%u,%u,%u", &address.h1, &address.h2, &address.h3,
        &address.h4, &address.p1, &address.p2) != 6) {
        send_response(client, FTP_ERROR_SYNTAX, "Invalid PORT command.");
        return -1;
    }
    make_adress(&address, client);
    send_response(client, FTP_COMMAND_OK, "PORT command successful.");
    return 0;
}
