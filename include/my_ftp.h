/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** my_ftp
*/

#pragma once

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUFF_SIZE 255
#define MAX_CLIENTS 10

typedef struct client_sock_s {
    int socket;
    char *rbuf;
    char *wbuf;
} client_sock_t;

typedef struct server_s {
    int socket;
    fd_set rfd;
    fd_set wfd;
    struct sockaddr_in addr;
    socklen_t len;
} server_t;

/// Clients
void new_client(client_sock_t *clients, int client_socket);
void remove_client(client_sock_t **clients, int remove_index);
void listen_clients(client_sock_t *clients, server_t *server);
void write_client_buff(client_sock_t *clients, int i, char *message);

/// Server
int configure_server(server_t *server, char *port_param);
void server_loop(client_sock_t *clients, server_t *server);
