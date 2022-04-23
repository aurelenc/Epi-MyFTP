/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_list
*/

#include "my_ftp.h"
#include <dirent.h>

static char *list_get_path(client_sock_t *clients, int id, params_t arg)
{
    char *path;

    if (arg.nb == 1)
        path = strdup(clients[id].path);
    else if (arg.nb == 2)
        path = get_clean_path(clients[id].path, arg.array[1]);
    else {
        return NULL;
    }
    return path;
}

static void list_files(client_sock_t *clients, int id, DIR *dir)
{
    char *buff;
    int pid = 0;

    buff = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
    if (!buff) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    pid = fork();
    if (pid == 0) {
        write_client_buff(clients, id, CODE_150);
        while (readdir(dir) != NULL) {
            sprintf(buff, "%s\r\n", readdir(dir)->d_name);
            write(clients[id].transfer_socket, buff, strlen(buff));
        }
        write_client_buff(clients, id, CODE_226);
    }
    free(buff);
}

void list_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    char *path = list_get_path(clients, id, arg);
    DIR *dir;

    if (!path) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    dir = opendir(path);
    if (!dir) {
        write_client_buff(clients, id, CODE_550);
        return;
    }
    list_files(clients, id, dir);
    closedir(dir);
    free(path);
}
