/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** my_ftp
*/

#pragma once

typedef struct client_socket_s {
    int socket;
    char *rbuf;
    char *wbuf;
} client_socket_t;
