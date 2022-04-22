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
        remove_client(&clients, i);
    strcat(clients[i].wbuf, message);
}
