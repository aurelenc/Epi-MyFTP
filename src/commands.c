/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands
*/

#include "my_ftp.h"

command_t commands[] = {
    {"USER", 1, 0, &user_command},
    {"PASS", 1, 0, &pass_command},
    {"CWD", 1, 0, &cwd_command},
    {"CDUP", 0, 0, &cdup_command},
    {"QUIT", 0, 0, &quit_command},
    {"DELE", 1, 0, &dele_command},
    {"PWD", 0, 0, &pwd_command},
    {"PASV", 0, 0, &pasv_command},
    {"PORT", 1, 0, &port_command},
    {"HELP", 0, 1, &help_command},
    {"NOOP", 0, 0, &noop_command},
    {"RETR", 1, 0, &retr_command},
    {"STOR", 1, 0, &stor_command},
    {"LIST", 0, 1, &list_command},
    {NULL, 0, 0, NULL}
};
