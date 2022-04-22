/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** clients
*/

#include "my_ftp.h"

void new_client(client_sock_t *clients, int client_socket)
{
    int i = 0;

    for (; i < MAX_CLIENTS && clients[i].socket != 0; i++);
    if (clients[i].socket) {
        dprintf(client_socket, "Too many connexions to server\n");
        return;
    }
    clients[i].socket = client_socket;
}

void remove_client(client_sock_t **clients, int remove_index)
{
    close(clients[remove_index]->socket);
    clients[remove_index]->socket = 0;
    memset(clients[remove_index]->rbuf, 0, MAX_BUFF_SIZE);
    memset(clients[remove_index]->wbuf, 0, MAX_BUFF_SIZE);
}

void handle_input(client_sock_t *clients, int i)
{
    printf("READ ON %d\n", clients[i].socket);
    if (read(clients[i].socket, clients[i].rbuf, MAX_BUFF_SIZE) == 0) {
        remove_client(&clients, i);
    }
    if (strncmp(clients[i].rbuf, "a", 1) == 0)
        write_client_buff(clients, i, "b\n");
}

void write_to_client(client_sock_t *client)
{
    printf("WRITE ON %d\n", client->socket);
    dprintf(client->socket, client->wbuf);
    memset(client->wbuf, 0, MAX_BUFF_SIZE);
}

void listen_clients(client_sock_t *clients, server_t *server)
{
    for (int i = 0; clients[i].socket != 0; i++) {
        if (FD_ISSET(clients[i].socket, &server->rfd))
            handle_input(clients, i);
        if (FD_ISSET(clients[i].socket, &server->wfd))
            write_to_client(&clients[i]);
    }
}
