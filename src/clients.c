/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** clients
*/

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
