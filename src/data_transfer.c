/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-myftp-nolan.papa
** File description:
** data_transfer
*/

#include "../include/commands.h"
#include "../include/response.h"
#include <string.h>
#include <unistd.h>

int error_passif_socket(int sockfd, struct sockaddr_in *data_addr,
    socklen_t *addr_len)
{
    if (bind(sockfd, (struct sockaddr *)data_addr, *addr_len) < 0) {
        close(sockfd);
        return -1;
    }
    if (listen(sockfd, 1) < 0) {
        close(sockfd);
        return -1;
    }
    if (getsockname(sockfd, (struct sockaddr *)data_addr, addr_len) < 0) {
        close(sockfd);
        return -1;
    }
    return 0;
}

int create_passive_socket(client_t *client)
{
    int sockfd;
    struct sockaddr_in data_addr;
    socklen_t addr_len = sizeof(data_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return -1;
    }
    memset(&data_addr, 0, sizeof(data_addr));
    data_addr.sin_family = AF_INET;
    data_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    data_addr.sin_port = 0;
    if (error_passif_socket(sockfd, &data_addr, &addr_len) == -1)
        return -1;
    client->data_addr = data_addr;
    return sockfd;
}
