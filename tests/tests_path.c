/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** tests_path
*/

#include <criterion/criterion.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include "../include/my_ftp.h"

client_sock_t *init_clients(void);

Test(pwd, root)
{
    client_sock_t *clients = init_clients();
    char *params[1] = {"PWD"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    pwd_command(clients, 0, NULL, (params_t){params, 1});
    cr_assert(strcmp(clients[0].wbuf, "257 \"/\" created.\r\n") == 0);
}

Test(cwd, root)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"CWD", "/home"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    cwd_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(strcmp(clients[0].wbuf, CODE_250) == 0);
    cr_assert(strcmp(clients[0].path, "/home") == 0);
}

Test(cwd, home)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"CWD", "home"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    cwd_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(strcmp(clients[0].wbuf, CODE_250) == 0);
    cr_assert(strcmp(clients[0].path, "/home") == 0);
}

Test(cwd, bad_args)
{
    client_sock_t *clients = init_clients();
    char *params[1] = {"CWD"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    cwd_command(clients, 0, NULL, (params_t){params, 1});
    cr_assert(strcmp(clients[0].wbuf, CODE_501) == 0);
}

Test(cdup, root)
{
    client_sock_t *clients = init_clients();
    char *params[1] = {"CDUP"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    cdup_command(clients, 0, NULL, (params_t){params, 1});
    cr_assert(strcmp(clients[0].wbuf, CODE_550) == 0);
    cr_assert(strcmp(clients[0].path, "/") == 0);
}

Test(cdup, home)
{
    client_sock_t *clients = init_clients();
    char *params[1] = {"CDUP"};

    if (!clients)
        return;
    new_client(clients, 1, "/home");
    cdup_command(clients, 0, NULL, (params_t){params, 1});
    cr_assert(strcmp(clients[0].wbuf, CODE_200) == 0);
    cr_assert(strcmp(clients[0].path, "/") == 0);
}

Test(cdup, bad_arg)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"CDUP", "AAAAAAAA"};

    if (!clients)
        return;
    new_client(clients, 1, "/home");
    cdup_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(strcmp(clients[0].wbuf, CODE_501) == 0);
}

Test(dele, bad_arg)
{
    client_sock_t *clients = init_clients();
    char *params[1] = {"DELE"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    dele_command(clients, 0, NULL, (params_t){params, 1});
    cr_assert(strcmp(clients[0].wbuf, CODE_501) == 0);
}

Test(dele, bad_file)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"DELE", "AAAAAAAA"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    dele_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(strcmp(clients[0].wbuf, CODE_550) == 0);
}

Test(dele, good_file)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"DELE", "good_file"};
    int fd = open("/tmp/good_file", O_RDWR | O_CREAT, 0777);

    if (fd == -1)
        return;
    close(fd);
    if (!clients)
        return;
    new_client(clients, 1, "/tmp");
    dele_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(strcmp(clients[0].wbuf, CODE_250) == 0);
}

Test(get_clean_path, first)
{
    char *path = get_clean_path("/home", NULL);

    cr_assert(strcmp(path, "/home") == 0);
}

Test(get_clean_path, second)
{
    char *path = get_clean_path(NULL, "/home");

    cr_assert(strcmp(path, "/home") == 0);
}

Test(get_clean_path, both)
{
    char *path = get_clean_path("/home", "aurele");

    cr_assert(strcmp(path, "/home/aurele") == 0);
}

Test(get_clean_path, root)
{
    char *path = get_clean_path("/home", "/tmp");

    cr_assert(strcmp(path, "/tmp") == 0);
}
