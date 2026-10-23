/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_quit
*/

#include "../../include/commands.h"
#include "../../include/response.h"

int handle_quit(client_t *client, const char *arg)
{
    (void)arg;
    send_response(client, FTP_GOODBYE, "Goodbye.");
    return -2;
}
