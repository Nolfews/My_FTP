/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_noop
*/

#include "../../include/commands.h"
#include "../../include/response.h"

int handle_noop(client_t *client, const char *arg)
{
    (void)arg;
    send_response(client, FTP_COMMAND_OK, "NOOP ok.");
    return 0;
}
