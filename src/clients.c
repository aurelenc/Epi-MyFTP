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
    if (clients[i]->socket) {
        dprintf(client_socket, "Too many connexions to server\n");
        return;
    }
    clients[i]->socket = client_socket;
    clients[i]->rbuf = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
    clients[i]->wbuf = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
}

static void remove_client(client_sock_t **clients, int remove_index)
{
    close(clients[remove_index]->socket);
    clients[remove_index]->socket = 0;
    memset(clients[remove_index]->rbuf, 0, MAX_BUFF_SIZE);
    memset(clients[remove_index]->wbuf, 0, MAX_BUFF_SIZE);
}

void listen_clients(client_sock_t *clients, fd_set *rfd)
{
    for (int i = 0; clients[i].socket != 0; i++) {
        printf("%d", clients[i].socket);
        if (FD_ISSET(clients[i].socket, rfd)) {
            if (read(clients[i].socket, clients[i].rbuf, MAX_BUFF_SIZE) == 0) {
                remove_client(&clients, i);
                continue;
            }
            if (strncmp(clients[i].rbuf, "a", 1) == 0)
                dprintf(clients[i].socket, "b\n");
        }
    }
}
