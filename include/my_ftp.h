/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** my_ftp
*/

#pragma once

#define MAX_BUFF_SIZE 255
#define MAX_CLIENTS 10

typedef struct client_socket_s {
    int socket;
    char *rbuf;
    char *wbuf;
} client_socket_t;
