/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_cwd
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "../../include/commands.h"
#include "../../include/response.h"

void make_cwd(const char *path, char *new_path, client_t *client)
{
    if (strcmp(path, "/") == 0) {
        strncpy(client->current_dir, client->server_root, PATH_MAX);
        send_response(client, FTP_FILE_ACTION_COMPLETED,
            "Returned to server root.");
    } else if (chdir(new_path) == 0) {
        realpath(new_path, client->current_dir);
        send_response(client, FTP_FILE_ACTION_COMPLETED,
            "Directory changed successfully.");
    } else {
        send_response(client, FTP_ERROR_FILE_UNAVAIL,
            "Failed to change directory.");
    }
}

int handle_cwd(client_t *client, const char *path)
{
    char new_path[PATH_MAX];

    if (path == NULL || strlen(path) == 0) {
        send_response(client, FTP_ERROR_SYNTAX, "Syntax error in parameters.");
        return -1;
    }
    if (snprintf(new_path, sizeof(new_path), "%s/%s",
        client->current_dir, path) >= (int)sizeof(new_path)) {
        send_response(client, FTP_ERROR_GENERIC, "Path too long.");
        return -1;
    }
    if (strcmp(path, "..") == 0 && strcmp(client->server_root,
        client->current_dir) == 0) {
        send_response(client, FTP_ERROR_FILE_UNAVAIL, "ALready at root");
        return -1;
    }
    make_cwd(path, new_path, client);
    return 0;
}
