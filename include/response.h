/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** response
*/

#ifndef RESPONSE_H
    #define RESPONSE_H

    #include "server.h"

    #define FTP_READY_FOR_NEW_USER     220
    #define FTP_GOODBYE                221
    #define FTP_TRANSFER_STARTING      150
    #define FTP_TRANSFER_COMPLETE      226
    #define FTP_PASSIVE_MODE           227
    #define FTP_LOGIN_SUCCESSFUL       230
    #define FTP_FILE_ACTION_COMPLETED  250
    #define FTP_PWD_REPLY              257
    #define FTP_USERNAME_OK            331
    #define FTP_NEED_ACCOUNT           332
    #define FTP_ERROR_GENERIC          501
    #define FTP_ERROR_SYNTAX           500
    #define FTP_ERROR_NOT_LOGGED       530
    #define FTP_ERROR_FILE_UNAVAIL     550
    #define FTP_COMMAND_OK             200
    #define FTP_HELP_MESSAGE           214
    #define FTP_ERROR_NOT_IMPLEMENTED  502

typedef struct {
    int code;
    const char *msg;
} ftp_response_t;

void send_response(client_t *client, int code, const char *message);
void send_multiline_response(client_t *client, int code, const char **messages,
    int count);

#endif
