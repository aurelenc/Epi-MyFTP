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
    memset(clients[i].rbuf, 0, MAX_BUFF_SIZE);
    memset(clients[i].wbuf, 0, MAX_BUFF_SIZE);
    memset(clients[i].user, 0, MAX_BUFF_SIZE);
    memset(clients[i].pass, 0, MAX_BUFF_SIZE);
    clients[i].pass[0] = ' ';
    dprintf(client_socket, CODE_220);
}

void remove_client(client_sock_t *clients, int remove_index)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].socket == remove_index) {
            // shutdown(clients[i].socket, SHUT_RDWR);
            close(clients[i].socket);
            clients[i].socket = 0;
            return;
        }
    }
}

void write_to_client(client_sock_t *client)
{
    dprintf(client->socket, client->wbuf);
    memset(client->wbuf, 0, MAX_BUFF_SIZE);
}

void listen_clients(client_sock_t *clients, server_t *server)
{
    for (int i = 0; clients[i].socket != 0; i++) {
        if (FD_ISSET(clients[i].socket, &server->rfd))
            handle_input(clients, i);
        // if (FD_ISSET(clients[i].socket, &server->wfd))
        write_to_client(&clients[i]);
    }
}
