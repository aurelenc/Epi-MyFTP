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
#include "reply_codes.h"

#define MAX_BUFF_SIZE 255
#define MAX_CLIENTS 10
#define MAX_ARGS_NB 1
#define MAX_PARAMS_NB MAX_ARGS_NB + 1

typedef struct client_sock_s {
    int socket;
    char *rbuf;
    char *wbuf;
    char *user;
    char *pass;
    bool is_logged;
} client_sock_t;

typedef struct command_s {
    char *cmd;
    int required_params_nb;
    int optional_params_nb;
    void (*func)(client_sock_t *clients, int id, char **params, int params_nb);
} command_t;

typedef struct server_s {
    int socket;
    fd_set rfd;
    fd_set wfd;
    struct sockaddr_in addr;
    socklen_t len;
} server_t;

extern command_t commands[];

/// Clients
void new_client(client_sock_t *clients, int client_socket);
void remove_client(client_sock_t *clients, int remove_index);
void listen_clients(client_sock_t *clients, server_t *server);
void write_client_buff(client_sock_t *clients, int i, char *message);
void handle_input(client_sock_t *clients, int id);

/// Server
int configure_server(server_t *server, char *port_param);
void server_loop(client_sock_t *clients, server_t *server);

/// Commands
void user_command(client_sock_t *clients, int id, char **args, int params_nb);
void pass_command(client_sock_t *clients, int id, char **args, int params_nb);
void quit_command(client_sock_t *clients, int id, char **args, int params_nb);
void help_command(client_sock_t *clients, int id, char **args, int params_nb);
void noop_command(client_sock_t *clients, int id, char **args, int params_nb);
void cwd_command(client_sock_t *clients, int id, char **args, int params_nb);
void cdup_command(client_sock_t *clients, int id, char **args, int params_nb);
void pwd_command(client_sock_t *clients, int id, char **args, int params_nb);
void dele_command(client_sock_t *clients, int id, char **args, int params_nb);
void retr_command(client_sock_t *clients, int id, char **args, int params_nb);
void stor_command(client_sock_t *clients, int id, char **args, int params_nb);
void list_command(client_sock_t *clients, int id, char **args, int params_nb);
void pasv_command(client_sock_t *clients, int id, char **args, int params_nb);
void port_command(client_sock_t *clients, int id, char **args, int params_nb);
