/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** my_ftp
*/

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my_ftp.h"

void new_client(client_sock_t **clients, int client_socket)
{
    int i = 0;

    for (; clients[i]->socket != 0 && i < MAX_CLIENTS; i++);
    if (clients[i]->socket)
        return;
    clients[i]->socket = client_socket;
    clients[i]->rbuf = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
    clients[i]->wbuf = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
}

void listen_clients(client_sock_t *clients, fd_set *rfd)
{
    for (int i = 0; clients[i].socket != 0; i++) {
        printf("%d", clients[i].socket);
        if (FD_ISSET(clients[i].socket, rfd)) {
            read(clients[i].socket, clients[i].rbuf, MAX_BUFF_SIZE);
            if (strncmp(clients[i].rbuf, "a", 1) == 0)
                dprintf(clients[i].socket, "b\n");
        }
    }
}

void ftp_loop(client_sock_t *clients, server_t *server)
{
    FD_ZERO(&server->rfd);
    FD_ZERO(&server->wfd);
    FD_SET(server->socket, &server->rfd);
    for (int i = 0; clients[i].socket != 0; i++)
        FD_SET(clients[i].socket, &server->rfd);
    select(FD_SETSIZE, &server->rfd, &server->wfd, NULL, NULL);
    if (FD_ISSET(server->socket, &server->rfd)) {
        new_client(&clients, accept(server->socket,
        (struct sockaddr *)&server->addr, &server->len));
    }
    listen_clients(clients, &server->rfd);
}

int my_ftp(int ac, char **av)
{
    server_t server;
    client_sock_t *clients = calloc(sizeof(client_sock_t), MAX_CLIENTS + 1);

    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!server.socket)
        return 84;
    server.addr.sin_family = AF_INET;
    server.addr.sin_port = htons(atoi(av[1]));
    server.addr.sin_addr.s_addr = INADDR_ANY;
    server.len = sizeof(server.addr);
    if (bind(server.socket, (struct sockaddr *)&server.addr, server.len) < 0)
        return 84;
    if (listen(server.socket, MAX_CLIENTS) < 0)
        return 84;
    setbuf(stdout, NULL);
    while (1)
        ftp_loop(clients, &server);
    close(server.socket);
    return 0;
}
