/*
** EPITECH PROJECT, 2022
** Epi-MyFTP
** File description:
** reply_codes
*/

#pragma once

#define CODE_120 "120 Service ready in nnn minutes.\r\n"
#define CODE_125 "125 Data connection already open; transfer starting.\r\n"
#define CODE_150 "150 File status okay; about to open data connection.\r\n"
#define CODE_200 "200 Command okay.\r\n"
#define CODE_214 "214 Commands: USER PASS CWD CDUP QUIT DELE PWD PASV PORT\
HELP NOOP RETR STOR LIST.\r\n"
#define CODE_220 "220 Service ready for new user.\r\n"
#define CODE_221 "221 Service closing control connection.\r\n"
#define CODE_226 "226 Closing data connection.\r\n"
#define CODE_227 "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n"
#define CODE_230 "230 User logged in, proceed.\r\n"
#define CODE_250 "250 Requested file action okay, completed.\r\n"
#define CODE_257 "257 \"%s\" created.\r\n"
#define CODE_331 "331 User name okay, need password.\r\n"
#define CODE_332 "332 Need account for login.\r\n"

#define CODE_425 "425 Can't open data connection.\r\n"
#define CODE_430 "430 Invalid username or password.\r\n"
#define CODE_451 "451 Requested action aborted. Local error in processing.\r\n"
#define CODE_501 "501 Syntax error in parameters or arguments.\r\n"
#define CODE_530 "530 Not logged in.\r\n"
#define CODE_550 "550 Requested action not taken.\r\n"
#define CODE_10068 "10068 Too many users, server is full.\r\n"
