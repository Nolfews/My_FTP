/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_pwd
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <stdio.h>
#include <string.h>

int handle_pwd(client_t *client, const char *arg)
{
    char response[BUFFER_SIZE];
    char truncated_path[BUFFER_SIZE];
    const char *prefix = "\"";
    const char *suffix = "\" is current directory.";
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    size_t max_path_len = BUFFER_SIZE - prefix_len - suffix_len - 1;

    (void)arg;
    strncpy(truncated_path, client->current_dir, max_path_len);
    truncated_path[max_path_len - 1] = '\0';
    strncpy(response, prefix, BUFFER_SIZE);
    strncat(response, truncated_path, BUFFER_SIZE - strlen(response) - 1);
    strncat(response, suffix, BUFFER_SIZE - strlen(response) - 1);
    send_response(client, FTP_PWD_REPLY, response);
    return 0;
}
