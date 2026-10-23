/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_cdup
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "../../include/commands.h"
#include "../include/response.h"

int handle_cdup(client_t *client, const char *arg)
{
    (void)arg;
    if (chdir("..") == 0) {
        realpath("..", client->current_dir);
        send_response(client, FTP_COMMAND_OK, "Moved to parent directory.");
    } else {
        send_response(client, FTP_ERROR_FILE_UNAVAIL,
            "Failed to move to parent directory.");
    }
    return 0;
}
