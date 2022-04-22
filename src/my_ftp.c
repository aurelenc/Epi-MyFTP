/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** my_ftp
*/

#include "my_ftp.h"

static bool has_param_error(int ac, char **av)
{
    if (ac == 2) {
        if (strcmp(av[1], "-help") == 0)
            return false;
        return true;
    }
    if (ac != 3)
        return true;
    return false;
}

static int display_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("      port  is the port number on which the \
server socket listens\n");
    printf("      path  is the path to the home directory \
for the Anonymous user\n");
    return 0;
}

client_sock_t *init_clients(void)
{
    client_sock_t *clients = calloc(sizeof(client_sock_t), MAX_CLIENTS + 1);

    if (!clients)
        return NULL;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].socket = 0;
        clients[i].rbuf = calloc(sizeof(char), MAX_BUFF_SIZE);
        clients[i].wbuf = calloc(sizeof(char), MAX_BUFF_SIZE);
        if (!clients[i].rbuf || !clients[i].wbuf)
            return NULL;
    }
    return clients;
}

int my_ftp(int ac, char **av)
{
    server_t server;
    client_sock_t *clients;

    if (has_param_error(ac, av))
        return 84;
    if (ac == 2)
        return display_help();
    if (configure_server(&server, av[1]) < 0)
        return 84;
    clients = init_clients();
    if (!clients) {
        close(server.socket);
        return 84;
    }
    setbuf(stdout, NULL);
    while (1)
        server_loop(clients, &server);
    close(server.socket);
    return 0;
}
