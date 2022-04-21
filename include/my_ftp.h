/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** my_ftp
*/

#pragma once

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
