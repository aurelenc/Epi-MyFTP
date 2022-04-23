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

void exec_cmd(client_sock_t *clients, int id, int command_id, params_t params)
{
    bool require_auth = true;

    for (int i = 0; i < COMMAND_ENUM_SIZE; i++) {
        if (no_auth_commands[i] == command_id) {
            require_auth = false;
            break;
        }
    }
    if (require_auth && !clients[id].is_logged) {
        write_client_buff(clients, id, CODE_530);
        return;
    }
    commands[command_id].func(clients, id, params.array, params.nb);
}

void handle_input(client_sock_t *clients, int id)
{
    params_t params;

    params.nb = 0;
    params.array = calloc(sizeof(char *), MAX_PARAMS_NB + 1);
    if (!params.array ||
        read(clients[id].socket, clients[id].rbuf, MAX_BUFF_SIZE) == 0) {
        remove_client(clients, id);
        return;
    }
    params.nb = get_command_params(params.array, clients[id].rbuf);
    for (enum command_e i = 0; i < COMMAND_ENUM_SIZE; i++) {
        if (strncmp(clients[id].rbuf, commands[i].cmd,
            strlen(commands[i].cmd)) == 0) {
                exec_cmd(clients, id, i, params);
            memset(clients[id].rbuf, 0, MAX_BUFF_SIZE);
            break;
        }
    }
}
