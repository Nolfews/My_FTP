/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** handle_list
*/

#include "../../include/commands.h"
#include "../../include/response.h"
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void setup_path(client_t *client, const char *path, char *list_path,
    size_t size_path)
{
    if (path && *path)
        snprintf(list_path, size_path, "%s/%s", client->current_dir, path);
    else
        strncpy(list_path, client->current_dir, size_path);
    list_path[size_path - 1] = '\0';
}

static void print_message(char *file_info, struct dirent *entry,
    struct stat *st)
{
    snprintf(file_info, BUFFER_SIZE + 50,
        "%c%c%c%c%c%c%c%c%c%c %10lld %s\r\n",
        (S_ISDIR(st->st_mode)) ? 'd' : '-',
        (st->st_mode & S_IRUSR) ? 'r' : '-',
        (st->st_mode & S_IWUSR) ? 'w' : '-',
        (st->st_mode & S_IXUSR) ? 'x' : '-',
        (st->st_mode & S_IRGRP) ? 'r' : '-',
        (st->st_mode & S_IWGRP) ? 'w' : '-',
        (st->st_mode & S_IXGRP) ? 'x' : '-',
        (st->st_mode & S_IROTH) ? 'r' : '-',
        (st->st_mode & S_IWOTH) ? 'w' : '-',
        (st->st_mode & S_IXOTH) ? 'x' : '-',
        (long long)st->st_size,
        entry->d_name);
}

static void read_list(DIR *dir, char *list_path, client_t *client)
{
    struct dirent *entry = readdir(dir);
    char file_info[BUFFER_SIZE + 50];
    struct stat st;
    char full_path[PATH_MAX];

    while (entry != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", list_path,
            entry->d_name);
        if (stat(full_path, &st) == 0) {
            print_message(file_info, entry, &st);
            write(client->data_socket, file_info, strlen(file_info));
        }
        entry = readdir(dir);
    }
}

static int handle_establish_data_connection(DIR *dir, client_t *client)
{
    if (establish_data_connection(client) < 0) {
        closedir(dir);
        send_response(client, FTP_ERROR_GENERIC,
            "Failed to establish connection.");
        return -1;
    }
    return 0;
}

int handle_list(client_t *client, const char *path)
{
    DIR *dir;
    char list_path[PATH_MAX];

    setup_path(client, path, list_path, sizeof(list_path));
    dir = opendir(list_path);
    if (!dir) {
        send_response(client, FTP_ERROR_FILE_UNAVAIL, "Failed to open dir.");
        return -1;
    }
    send_response(client, FTP_TRANSFER_STARTING, "Here comes the dir listen.");
    if (handle_establish_data_connection(dir, client) == -1)
        return -1;
    read_list(dir, list_path, client);
    closedir(dir);
    close(client->data_socket);
    client->data_socket = -1;
    send_response(client, FTP_TRANSFER_COMPLETE, "Directory send OK.");
    return 0;
}
