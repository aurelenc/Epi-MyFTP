/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands_mode
*/

#include "my_ftp.h"

static int set_transfer_socket(client_id_t *cid, server_t *srv, int port)
{
    struct sockaddr_in sockaddr;
    socklen_t socklen = sizeof(sockaddr);

    if (cid->clients[cid->id].transfer_socket > 0)
        close(cid->clients[cid->id].transfer_socket);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    cid->clients[cid->id].transfer_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (cid->clients[cid->id].transfer_socket < 0)
        return -1;
    if (bind(cid->clients[cid->id].transfer_socket, (struct sockaddr *)&sockaddr,
        socklen) < 0)
        return -1;
    getsockname(cid->clients[cid->id].transfer_socket, (struct sockaddr *)&sockaddr, &socklen);
    port = ntohs(sockaddr.sin_port);
    return port;
}

static int *get_ip_segments(char *ip)
{
    int *segments = calloc(sizeof(int), 5);

    if (segments == NULL)
        return NULL;
    if (ip == NULL)
        return NULL;
    if (sscanf(ip, "%d.%d.%d.%d",
        &segments[0], &segments[1], &segments[2], &segments[3]) != 4)
        return NULL;
    return segments;
}

void pasv_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    char *buff;
    client_id_t cid = {.clients = clients, .id = id};
    int port = set_transfer_socket(&cid, srv, 0);
    struct in_addr in_addr = srv->addr.sin_addr;
    int *ip_segments = get_ip_segments(inet_ntoa(in_addr));

    if (!ip_segments || port < 0) {
        write_client_buff(clients, id, CODE_425);
        return;
    }
    clients[id].is_passive = true;
    buff = calloc(sizeof(char), strlen(CODE_227) + (3*6) + 1);
    if (!buff) {
        write_client_buff(clients, id, CODE_451);
        return;
    }
    sprintf(buff, CODE_227, ip_segments[0], ip_segments[1], ip_segments[2],
        ip_segments[3], port / 256, port % 256);
    write_client_buff(clients, id, buff);
    free(buff);
}

void port_command(client_sock_t *clients, int id, server_t *srv, params_t arg)
{
    client_id_t cid = {.clients = clients, .id = id};
    int port = atoi(arg.array[1]);

    if (arg.nb != 2 || port == 0) {
        write_client_buff(clients, id, CODE_501);
        return;
    }
    port = set_transfer_socket(&cid, srv, port);
    if (port < 0) {
        write_client_buff(clients, id, CODE_425);
        return;
    }
    clients[id].is_passive = false;
    write_client_buff(clients, id, CODE_200);
}
