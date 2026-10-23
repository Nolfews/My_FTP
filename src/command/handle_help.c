/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_help
*/

#include "../../include/commands.h"
#include "../../include/response.h"

int handle_help(client_t *client, const char *arg)
{
    const char *help_msg[] = {
        "The following commands are supported:\n",
        "USER\nPASS\nPWD\nCWD\nCDUP\n",
        "PASV\nPORT\nLIST\nRETR\nSTOR\n",
        "DELE\nHELP\nNOOP\nQUIT"
    };

    (void)arg;
    send_multiline_response(client, FTP_HELP_MESSAGE, help_msg, 4);
    return 0;
}
