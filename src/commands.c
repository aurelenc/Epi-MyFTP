/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands
*/

#include "my_ftp.h"

const command_t commands[] = {
    {USER_COMMAND, "USER", 1, 0, &user_command},
    {PASS_COMMAND, "PASS", 1, 0, &pass_command},
    {CWD_COMMAND, "CWD", 1, 0, &cwd_command},
    {CDUP_COMMAND, "CDUP", 0, 0, &cdup_command},
    {QUIT_COMMAND, "QUIT", 0, 0, &quit_command},
    {DELE_COMMAND, "DELE", 1, 0, &dele_command},
    {PWD_COMMAND, "PWD", 0, 0, &pwd_command},
    {PASV_COMMAND, "PASV", 0, 0, &pasv_command},
    {PORT_COMMAND, "PORT", 1, 0, &port_command},
    {HELP_COMMAND, "HELP", 0, 1, &help_command},
    {NOOP_COMMAND, "NOOP", 0, 0, &noop_command},
    {RETR_COMMAND, "RETR", 1, 0, &retr_command},
    {STOR_COMMAND, "STOR", 1, 0, &stor_command},
    {LIST_COMMAND, "LIST", 0, 1, &list_command},
    {COMMAND_ENUM_SIZE, NULL, 0, 0, NULL}
};

const enum command_e no_auth_commands[] = {
    USER_COMMAND,
    PASS_COMMAND,
    QUIT_COMMAND,
    HELP_COMMAND,
    NOOP_COMMAND,
    COMMAND_ENUM_SIZE
};
