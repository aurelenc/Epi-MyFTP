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

void new_client(client_socket_t **clients, int client_socket)
{
    int i = 0;

    for (; clients[i]->socket != 0; i++);
    if (!clients[i]->socket)
        return;
    clients[i]->socket = client_socket;
    clients[i]->rbuf = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
    clients[i]->wbuf = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
}

int my_ftp(int ac, char **av)
{
    fd_set rfd;
    fd_set wfd;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // int client_socket;
    struct sockaddr_in server_addr;
    socklen_t socklen;
    // char *buff = calloc(sizeof(char), 256);
    client_socket_t *clients = calloc(sizeof(client_socket_t), MAX_CLIENTS + 1);

    if (!server_socket)
        return 84;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(av[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    socklen = sizeof(server_addr);
    if (bind(server_socket, (struct sockaddr *)&server_addr, socklen) < 0)
        return 84;
    if (listen(server_socket, MAX_CLIENTS) < 0)
        return 84;
    setbuf(stdout, NULL);
    while (1) {
        FD_ZERO(&rfd);
        FD_ZERO(&wfd);
        FD_SET(server_socket, &rfd);

        select(FD_SETSIZE, &rfd, &wfd, NULL, NULL);
        if (FD_ISSET(server_socket, &rfd)) {
            new_client(&clients,
            accept(server_socket, (struct sockaddr *)&server_addr, &socklen));
        }
        for (int i = 0; clients[i].socket != 0; i++) {
            if (FD_ISSET(clients[i].socket, &rfd)) {
                read(clients[i].socket, clients[i].rbuf, MAX_BUFF_SIZE);
                if (strncmp(clients[i].rbuf, "bonjour", 7) == 0)
                    dprintf(clients[i].socket, "au revoir\n");
            }
        }
    }
    close(server_socket);
    return 0;
}
