/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_data
*/

#include <fcntl.h>
#include "my_ftp.h"

static void retr_file(client_sock_t *clients, int id, int fd)
{
    int pid = 0;
    char *buff;

    buff = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
    if (!buff) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    pid = fork();
    if (pid == 0) {
        write_client_buff(clients, id, CODE_150);
        while (read(fd, buff, MAX_BUFF_SIZE) > 0) {
            write(clients[id].transfer_socket, buff, MAX_BUFF_SIZE);
        }
        close(clients[id].transfer_socket);
        free(buff);
        write_client_buff(clients, id, CODE_226);
    }
}

static void stor_file(client_sock_t *clients, int id, int fd)
{
    int pid = 0;
    char *buff;

    buff = calloc(sizeof(char), MAX_BUFF_SIZE + 1);
    if (!buff) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    pid = fork();
    if (pid == 0) {
        write_client_buff(clients, id, CODE_150);
        while (read(clients[id].transfer_socket, buff, MAX_BUFF_SIZE) > 0) {
            write(fd, buff, MAX_BUFF_SIZE);
        }
        close(clients[id].transfer_socket);
        free(buff);
        write_client_buff(clients, id, CODE_226);
    }
}

void retr_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    int fd = 0;
    char *path;

    if (arg.nb != 2) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    path = get_clean_path(clients[id].path, arg.array[1]);
    if (!path) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        write_client_buff(clients, id, CODE_550);
        return;
    }
    retr_file(clients, id, fd);
    close(fd);
    free(path);
}

void stor_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    int fd = 0;
    char *path;

    if (arg.nb != 2) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    path = get_clean_path(clients[id].path, arg.array[1]);
    if (!path) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    fd = open(path, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        write_client_buff(clients, id, CODE_550);
        return;
    }
    stor_file(clients, id, fd);
    close(fd);
    free(path);
}

void list_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
}
