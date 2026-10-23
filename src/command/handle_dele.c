/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_dele
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <stdio.h>
#include <unistd.h>

int handle_dele(client_t *client, const char *filename)
{
    char filepath[PATH_MAX];

    if (snprintf(filepath, sizeof(filepath), "%s/%s",
            client->current_dir, filename) >= (int)sizeof(filepath)) {
        send_response(client, FTP_ERROR_FILE_UNAVAIL,
            "Path too long.");
        return -1;
    }
    if (unlink(filepath) < 0) {
        send_response(client, FTP_ERROR_FILE_UNAVAIL,
            "Failed to delete file.");
        return -1;
    }
    send_response(client, FTP_FILE_ACTION_COMPLETED,
        "File deleted successfully.");
    return 0;
}
