/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_path
*/

#include "my_ftp.h"

void cwd_command(client_sock_t *clients, int id, char **args, int params_nb)
{
}

void cdup_command(client_sock_t *clients, int id, char **args, int params_nb)
{
}

void pwd_command(client_sock_t *clients, int id, char **args, int params_nb)
{
    char *buff = calloc(sizeof(char), MAX_BUFF_SIZE);

    if (!buff)
        return;
    if (sprintf(buff, CODE_257, clients[id].path) < 0)
        return;
    write_client_buff(clients, id, buff);
    free(buff);
}

void dele_command(client_sock_t *clients, int id, char **args, int params_nb)
{
    char *buff;
    if (params_nb != 2) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    buff = calloc(sizeof(char), MAX_BUFF_SIZE);
    if (!buff)
        return;
    if (args[1][0] != '/')
        sprintf(buff, "%s/%s", clients[id].path, args[1]);
    else
        sprintf(buff, "%s", args[1]);
    if (remove(buff) == -1)
        write_client_buff(clients, id, CODE_550);
    else
        write_client_buff(clients, id, CODE_250);
    free(buff);
}
