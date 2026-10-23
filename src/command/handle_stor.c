/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_stor
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

static int handle_establish_data_connection(int file_fd, client_t *client)
{
    if (establish_data_connection(client) < 0) {
        close(file_fd);
        send_response(client, FTP_ERROR_GENERIC,
            "Failed to establish connection.");
        return -1;
    }
    return 0;
}

static void file_transfert(int file_fd, client_t *client)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client->data_socket, buffer, sizeof(buffer));

    while (bytes_read > 0) {
        write(file_fd, buffer, bytes_read);
        bytes_read = read(client->data_socket, buffer, sizeof(buffer));
    }
}

static void make_path(const char *filename, client_t *client, char *filepath,
    size_t current_dir_len)
{
    strncpy(filepath, client->current_dir, PATH_MAX - 1);
    filepath[PATH_MAX - 1] = '\0';
    if (current_dir_len < PATH_MAX - 1) {
        filepath[current_dir_len] = '/';
        filepath[current_dir_len + 1] = '\0';
        if (current_dir_len + 1 < PATH_MAX - 1) {
            strncpy(filepath + current_dir_len + 1, filename,
                    PATH_MAX - current_dir_len - 2);
            filepath[PATH_MAX - 1] = '\0';
        }
    }
}

static void finish_task(int file_fd, client_t *client)
{
    file_transfert(file_fd, client);
    close(file_fd);
    close(client->data_socket);
    client->data_socket = -1;
    send_response(client, FTP_TRANSFER_COMPLETE, "Transfer complete.");
}

int handle_stor(client_t *client, const char *filename)
{
    char filepath[PATH_MAX];
    int file_fd;
    size_t current_dir_len = strlen(client->current_dir);
    size_t filename_len = strlen(filename);

    if (current_dir_len + filename_len + 2 > PATH_MAX) {
        send_response(client, FTP_ERROR_FILE_UNAVAIL, "Path too long.");
        return -1;
    }
    make_path(filename, client, filepath, current_dir_len);
    file_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        send_response(client, FTP_ERROR_FILE_UNAVAIL, "Cannot create file.");
        return -1;
    }
    send_response(client, FTP_TRANSFER_STARTING, "Opening data connection.");
    if (handle_establish_data_connection(file_fd, client) == -1)
        return -1;
    finish_task(file_fd, client);
    return 0;
}
