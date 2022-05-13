/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** commands
*/

#include "my_ftp.h"

const command_t commands[] = {
    {"USER", 1, 0, &user_command, false},
    {"PASS", 1, 0, &pass_command, false},
    {"CWD", 1, 0, &cwd_command, true},
    {"CDUP", 0, 0, &cdup_command, true},
    {"QUIT", 0, 0, &quit_command, false},
    {"DELE", 1, 0, &dele_command, true},
    {"PWD", 0, 0, &pwd_command, true},
    {"PASV", 0, 0, &pasv_command, true},
    {"PORT", 1, 0, &port_command, true},
    {"HELP", 0, 1, &help_command, false},
    {"NOOP", 0, 0, &noop_command, false},
    {"RETR", 1, 0, &retr_command, true},
    {"STOR", 1, 0, &stor_command, true},
    {"LIST", 0, 1, &list_command, true},
    {"NULL", 0, 0, NULL, false}
};
