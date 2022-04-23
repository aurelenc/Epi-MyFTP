/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** server
*/

#include "my_ftp.h"

int configure_server(server_t *server, char *port_param, char *path_param)
{
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket < 0)
        return -1;
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(atoi(port_param));
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->len = sizeof(server->addr);
    server->default_path = path_param;
    if (bind(server->socket, (struct sockaddr *)&server->addr, server->len) < 0)
        return -1;
    if (listen(server->socket, MAX_CLIENTS) < 0)
        return -1;
    return 0;
}

void server_loop(client_sock_t *clients, server_t *server)
{
    FD_ZERO(&server->rfd);
    FD_ZERO(&server->wfd);
    FD_SET(server->socket, &server->rfd);
    for (int i = 0; clients[i].socket != 0; i++)
        FD_SET(clients[i].socket, &server->rfd);
    select(FD_SETSIZE, &server->rfd, &server->wfd, NULL, NULL);
    if (FD_ISSET(server->socket, &server->rfd)) {
        new_client(clients, accept(server->socket,
        (struct sockaddr *)&server->addr, &server->len), server->default_path);
    }
    listen_clients(clients, server);
}
