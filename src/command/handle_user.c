/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_user
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <string.h>
#include <stdio.h>

int handle_user(client_t *client, const char *username)
{
    if (username != NULL) {
        strncpy(client->username, username, MAX_USERNAME_LENGTH - 1);
        client->username[MAX_USERNAME_LENGTH - 1] = '\0';
        client->is_logged_with_user = 1;
        send_response(client, FTP_USERNAME_OK,
            "Anonymous login ok, send password.");
        return 0;
    }
    send_response(client, FTP_ERROR_NOT_LOGGED, "User not found.");
    return -1;
}
