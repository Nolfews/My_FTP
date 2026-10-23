/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handler_pass
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <string.h>
#include <stdio.h>

int handle_pass(client_t *client, const char *password)
{
    (void)password;
    if (!client->is_logged_with_user) {
        send_response(client, FTP_ERROR_SYNTAX, "Login with USER first.");
        return -1;
    }
    if (!client->is_authenticated) {
        if (strcmp(client->username, "Anonymous") == 0) {
            client->is_authenticated = 1;
            send_response(client, FTP_LOGIN_SUCCESSFUL, "Login successful.");
            return 0;
        } else {
            send_response(client, FTP_ERROR_NOT_LOGGED, "Login incorrect.");
            return -1;
        }
    }
    send_response(client, FTP_ERROR_SYNTAX, "Already logged in.");
    return -1;
}
