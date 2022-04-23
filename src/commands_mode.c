/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_mode
*/

#include "my_ftp.h"

void pasv_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    char *buff;

    clients[id].is_passive = 1;
    buff = calloc(sizeof(char), strlen(CODE_227) + (3*6) + 1);
    if (!buff) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    write_client_buff(clients, id, CODE_227);
}

void port_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
}
