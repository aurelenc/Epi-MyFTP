/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_base
*/

#include "my_ftp.h"
#include "reply_codes.h"

void user_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    if (arg.nb != 2) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    memset(clients[id].user, 0, MAX_USER_SIZE);
    strcpy(clients[id].user, arg.array[1]);
    if (strcmp(clients[id].user, "Anonymous") == 0) {
        if (strcmp(clients[id].pass, "") == 0) {
            clients[id].is_logged = true;
            write_client_buff(clients, id, CODE_230);
        } else {
            clients[id].is_logged = false;
            write_client_buff(clients, id, CODE_331);
        }
    } else {
        clients[id].is_logged = false;
        write_client_buff(clients, id, CODE_430);
    }
}

void pass_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    if (arg.nb > 2) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    memset(clients[id].pass, 0, MAX_PASS_SIZE);
    if (arg.nb == 2)
        strcpy(clients[id].pass, arg.array[1]);
    if (strcmp(clients[id].user, "Anonymous") == 0) {
        if (strcmp(clients[id].pass, "") == 0) {
            clients[id].is_logged = true;
            write_client_buff(clients, id, CODE_230);
        } else {
            clients[id].is_logged = false;
            write_client_buff(clients, id, CODE_430);
        }
    } else {
        clients[id].is_logged = false;
        write_client_buff(clients, id, CODE_332);
    }
}

void quit_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    dprintf(clients[id].socket, CODE_221);
    remove_client(clients, id);
}

void help_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    write_client_buff(clients, id, CODE_214);
}

void noop_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    write_client_buff(clients, id, CODE_200);
}
