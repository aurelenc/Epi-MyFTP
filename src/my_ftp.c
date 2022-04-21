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

int my_ftp(int ac, char **av)
{
    fd_set rfd;
    fd_set wfd;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int client_socket;
    struct sockaddr_in server_addr;
    socklen_t socklen;
    char *buff = calloc(sizeof(char), 256);

    if (!server_socket)
        return 84;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(av[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    socklen = sizeof(server_addr);
    if (bind(server_socket, (struct sockaddr *)&server_addr, socklen) < 0)
        return 84;
    if (listen(server_socket, 10) < 0)
        return 84;
    while (1) {
        FD_ZERO(&rfd);
        FD_ZERO(&wfd);
        FD_SET(server_socket, &rfd);

        select(FD_SETSIZE, &rfd, &wfd, NULL, NULL);
        if (FD_ISSET(server_socket, &rfd))
            client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &socklen);
        setbuf(stdout, NULL);
        // if (FD_ISSET(client_socket, &rfd)) {
            read(client_socket, buff, 255);
            if (strncmp(buff, "bonjour", 7) == 0)
                dprintf(client_socket, "au revoir\n");
        // }
    }
    close(server_socket);
    return 0;
}
