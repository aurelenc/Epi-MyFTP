/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** client_input
*/

#include "my_ftp.h"

void write_client_buff(client_sock_t *clients, int i, char *message)
{
    if (strlen(clients[i].wbuf) + strlen(message) > MAX_BUFF_SIZE)
        remove_client(clients, i);
    strcat(clients[i].wbuf, message);
}

int get_command_params(char **dest, char *src)
{
    int i = 0;

    for (; i < MAX_PARAMS_NB; i++) {
        dest[i] = strtok(i == 0 ? src : NULL, " \t\r\n");
        if (!dest[i])
            break;
    }
    return i;
}

void handle_input(client_sock_t *clients, int id)
{
    char **params = calloc(sizeof(char *), MAX_PARAMS_NB + 1);
    int params_nb = 0;

    if (!params ||
        read(clients[id].socket, clients[id].rbuf, MAX_BUFF_SIZE) == 0) {
        remove_client(clients, id);
        return;
    }
    params_nb = get_command_params(params, clients[id].rbuf);
    for (int i = 0; commands[i].cmd; i++) {
        if (strncmp(clients[id].rbuf, commands[i].cmd,
            strlen(commands[i].cmd)) == 0) {
            commands[i].func(clients, id, params, params_nb);
            memset(clients[id].rbuf, 0, MAX_BUFF_SIZE);
            break;
        }
    }
}
