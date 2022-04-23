/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** myftp_tests
*/

#include <criterion/criterion.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "../include/my_ftp.h"

client_sock_t *init_clients(void);

Test(github_action, test)
{
    cr_assert(0 == 0);
}

Test(user, username)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"USER", "Anonymous"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    user_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(clients[0].is_logged == false);
    cr_assert(strcmp(clients[0].user, "Anonymous") == 0);
}

Test(user, username_not_found)
{
    client_sock_t *clients = init_clients();
    char *params[2] = {"USER", "AAAAAAAA"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    user_command(clients, 0, NULL, (params_t){params, 2});
    cr_assert(clients[0].is_logged == false);
    cr_assert(strcmp(clients[0].user, "AAAAAAAA") == 0);
}

Test(user, no_username)
{
    client_sock_t *clients = init_clients();
    char *params[1] = {"USER"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    user_command(clients, 0, NULL, (params_t){params, 1});
    cr_assert(clients[0].is_logged == false);
    cr_assert(strcmp(clients[0].user, "") == 0);
}

Test(user, combo)
{
    client_sock_t *clients = init_clients();
    char *user[2] = {"USER", "Anonymous"};
    char *pass[2] = {"PASS", ""};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    pass_command(clients, 0, NULL, (params_t){pass, 2});
    user_command(clients, 0, NULL, (params_t){user, 2});
    cr_assert(clients[0].is_logged == true);
    cr_assert(strcmp(clients[0].user, "Anonymous") == 0);
    cr_assert(strcmp(clients[0].pass, "") == 0);
}

Test(password, bad_args)
{
    client_sock_t *clients = init_clients();
    char *pass[3] = {"PASS", "", "AAAAAAAA"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    pass_command(clients, 0, NULL, (params_t){pass, 3});
    cr_assert(clients[0].is_logged == false);
}

Test(password, cpy)
{
    client_sock_t *clients = init_clients();
    char *user[2] = {"USER", "Anonymous"};
    char *pass[2] = {"PASS", "abcd"};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    cr_assert(clients[0].pass, "");
    user_command(clients, 0, NULL, (params_t){user, 2});
    pass_command(clients, 0, NULL, (params_t){pass, 2});
    cr_assert(clients[0].pass, "abcd");
}

Test(password, combo)
{
    client_sock_t *clients = init_clients();
    char *user[2] = {"USER", "Anonymous"};
    char *pass[2] = {"PASS", ""};

    if (!clients)
        return;
    new_client(clients, 1, "/");
    user_command(clients, 0, NULL, (params_t){user, 2});
    pass_command(clients, 0, NULL, (params_t){pass, 2});
    cr_assert(clients[0].is_logged == true);
    cr_assert(strcmp(clients[0].user, "Anonymous") == 0);
    cr_assert(strcmp(clients[0].pass, "") == 0);
}
