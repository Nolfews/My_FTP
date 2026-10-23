/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** command_handler
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../include/commands.h"
#include "../include/response.h"

static const command_handler_t command_table[] = {
    {"USER", handle_user},
    {"PASS", handle_pass},
    {"PWD", handle_pwd},
    {"CWD", handle_cwd},
    {"CDUP", handle_cdup},
    {"PASV", handle_pasv},
    {"PORT", handle_port},
    {"LIST", handle_list},
    {"RETR", handle_retr},
    {"STOR", handle_stor},
    {"DELE", handle_dele},
    {"HELP", handle_help},
    {"NOOP", handle_noop},
    {"QUIT", handle_quit},
    {NULL, NULL}
};

command_handler_t *find_command_handler(const char *command)
{
    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strcmp(command_table[i].name, command) == 0) {
            return (command_handler_t *)&command_table[i];
        }
    }
    return NULL;
}
