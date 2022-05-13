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

#define MAX_BUFF_SIZE 2048
#define MAX_USER_SIZE 256
#define MAX_PASS_SIZE 256
#define MAX_PATH_SIZE 1024
#define MAX_CLIENTS 20
#define MAX_ARGS_NB 1
#define MAX_PARAMS_NB MAX_ARGS_NB + 1

typedef struct client_sock_s {
    int socket;
    bool is_logged;
    bool is_passive;
    int transfer_socket;
    char *rbuf;
    char *wbuf;
    char *user;
    char *pass;
    char *path;
} client_sock_t;

typedef struct client_id_s {
    client_sock_t *clients;
    int id;
} client_id_t;

typedef struct server_s {
    int socket;
    fd_set rfd;
    fd_set wfd;
    struct sockaddr_in addr;
    socklen_t len;
    char *default_path;
} server_t;

typedef struct params_s {
    char **array;
    int nb;
} params_t;

typedef struct command_s {
    char *cmd;
    int required_params_nb;
    int optional_params_nb;
    void (*func)(client_sock_t *, int, server_t *, params_t);
    bool auth_required;
} command_t;

extern const command_t commands[];

/// Clients
void new_client(client_sock_t *clients, int client_socket, char *default_path);
void remove_client(client_sock_t *clients, int remove_index);
void listen_clients(client_sock_t *clients, server_t *server);
void write_client_buff(client_sock_t *clients, int i, char *message);
void handle_input(client_sock_t *clients, int id, server_t *server);

/// Server
int configure_server(server_t *server, char *port_param, char *path_param);
void server_loop(client_sock_t *clients, server_t *server);
char *get_clean_path(char *path, char *add_path);

/// Commands
void user_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void pass_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void quit_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void help_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void noop_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void cwd_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void cdup_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void pwd_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void dele_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void retr_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void stor_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void list_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void pasv_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
void port_command(client_sock_t *clients, int id, server_t *srv, params_t arg);
