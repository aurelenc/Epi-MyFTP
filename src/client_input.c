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

void exec_cmd(client_id_t *cid, int command_id, server_t *srv, params_t args)
{
    bool require_auth = true;

    for (int i = 0; i < COMMAND_ENUM_SIZE; i++) {
        if (no_auth_commands[i] == command_id) {
            require_auth = false;
            break;
        }
    }
    if (require_auth && !cid->clients[cid->id].is_logged) {
        write_client_buff(cid->clients, cid->id, CODE_530);
        return;
    }
    commands[command_id].func(cid->clients, cid->id, srv, args);
}

void find_command(client_id_t *cid, int id, server_t *server, params_t params)
{
    bool command_found = false;

    for (enum command_e i = 0; i < COMMAND_ENUM_SIZE; i++) {
        if (strncmp(cid->clients[id].rbuf, commands[i].cmd,
            strlen(commands[i].cmd)) == 0) {
            exec_cmd(cid, i, server, params);
            memset(cid->clients[id].rbuf, 0, MAX_BUFF_SIZE);
            command_found = true;
            break;
        }
    }
    if (!command_found)
        write_client_buff(cid->clients, id, CODE_550);
}

void handle_input(client_sock_t *clients, int id, server_t *server)
{
    params_t params;
    client_id_t cid = {.clients = clients, .id = id};

    params.nb = 0;
    params.array = calloc(sizeof(char *), MAX_PARAMS_NB + 1);
    if (!params.array ||
        read(clients[id].socket, clients[id].rbuf, MAX_BUFF_SIZE) == 0) {
        remove_client(clients, id);
        return;
    }
    params.nb = get_command_params(params.array, clients[id].rbuf);
    find_command(&cid, id, server, params);
}
