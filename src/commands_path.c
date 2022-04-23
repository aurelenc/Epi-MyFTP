/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_path
*/

#include "my_ftp.h"

static char *get_clean_path(char *path, char *add_path)
{
    char *clean = NULL;

    if (path == NULL)
        return strdup(add_path);
    if (add_path == NULL)
        return strdup(path);
    if (add_path[0] == '/')
        return strdup(add_path);
    else {
        clean = calloc(sizeof(char), (strlen(path) + strlen(add_path) + 2));
        if (!clean)
            return NULL;
        strcpy(clean, path);
        strcat(clean, "/");
        strcat(clean, add_path);
    }
    return clean;
}

void cwd_command(client_sock_t *clients, int id, char **args, int params_nb)
{
    if (params_nb != 2) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    if (args[1][0] != '/') {
        if (clients[id].path[strlen(clients[id].path) - 1] != '/')
            strcat(clients[id].path, "/");
        strcat(clients[id].path, args[1]);
    } else {
        memset(clients[id].path, 0, MAX_PATH_SIZE);
        strcpy(clients[id].path, args[1]);
    }
    write_client_buff(clients, id, CODE_250);
}

void cdup_command(client_sock_t *clients, int id, char **args, int params_nb)
{
    if (params_nb != 1) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    if (strcmp(clients[id].path, "/") == 0) {
        write_client_buff(clients, id, CODE_550);
        return;
    }
    if (clients[id].path[strlen(clients[id].path) - 1] == '/')
        clients[id].path[strlen(clients[id].path) - 1] = '\0';
    for (int i = strlen(clients[id].path); i > 0; i--) {
        if (clients[id].path[i] == '/') {
            clients[id].path[i] = '\0';
            break;
        }
    }
    write_client_buff(clients, id, CODE_250);
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
    buff = get_clean_path(clients[id].path, args[1]);
    if (buff == NULL) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    if (remove(buff) == -1)
        write_client_buff(clients, id, CODE_550);
    else
        write_client_buff(clients, id, CODE_250);
    free(buff);
}
