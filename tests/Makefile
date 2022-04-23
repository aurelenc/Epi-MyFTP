##
## EPITECH PROJECT, 2022
## MyFTP
## File description:
## Makefile
##

NAME	=	unit_tests

SRC	=	../src/my_ftp.c\
		../src/server.c\
		../src/clients.c\
		../src/client_input.c\
		../src/commands.c\
		../src/commands_base.c\
		../src/commands_path.c\
		../src/commands_data.c\
		../src/commands_mode.c\
		../src/commands_list.c\

TEST_SRC	=	tests_my_ftp.c

CFLAGS	=	-Wall -Werror

LDFLAGS = -lcriterion --coverage -I ../include/

CC	=	gcc

$(NAME):
	$(CC) $(SRC) $(TEST_SRC) -o $(NAME) ${LDFLAGS}

clean:
	rm -f *.gc*

fclean: clean
	rm -f $(NAME)

all:	$(NAME)

.PHONY: $(NAME) clean fclean all
