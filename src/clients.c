/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** clients
*/

#include "my_ftp.h"

void new_client(client_sock_t *clients, int client_socket, char *default_path)
{
    int i = 0;

    for (; i < MAX_CLIENTS - 1 && clients[i].socket != 0; i++);
    if (clients[i].socket) {
        dprintf(client_socket, CODE_10068);
        return;
    }
    clients[i].socket = client_socket;
    clients[i].is_logged = false;
    clients[i].is_passive = 1;
    clients[i].transfer_socket = 0;
    memset(clients[i].rbuf, 0, MAX_BUFF_SIZE);
    memset(clients[i].wbuf, 0, MAX_BUFF_SIZE);
    memset(clients[i].user, 0, MAX_USER_SIZE);
    memset(clients[i].pass, 0, MAX_PASS_SIZE);
    clients[i].pass[0] = ' ';
    memset(clients[i].path, 0, MAX_PATH_SIZE);
    if (strlen(default_path) > MAX_PATH_SIZE)
        strcpy(clients[i].path, "/");
    else
        strcpy(clients[i].path, default_path);
    dprintf(client_socket, CODE_220);
}

void remove_client(client_sock_t *clients, int remove_index)
{
    shutdown(clients[remove_index].socket, SHUT_RDWR);
    close(clients[remove_index].socket);
    clients[remove_index].socket = 0;
}

void write_to_client(client_sock_t *client)
{
    dprintf(client->socket, client->wbuf);
    memset(client->wbuf, 0, MAX_BUFF_SIZE);
}

void listen_clients(client_sock_t *clients, server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS && clients[i].socket != 0; i++) {
        if (FD_ISSET(clients[i].socket, &server->rfd))
            handle_input(clients, i, server);
        // if (FD_ISSET(clients[i].socket, &server->wfd))
        write_to_client(&clients[i]);
    }
}
