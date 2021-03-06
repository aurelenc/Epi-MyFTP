##
## EPITECH PROJECT, 2022
## MyFTP
## File description:
## Makefile
##

NAME	=	myftp

TESTS_NAME	=	unit_tests

SRC	=	src/main.c\
		src/my_ftp.c\
		src/server.c\
		src/clients.c\
		src/client_input.c\
		src/commands.c\
		src/commands_base.c\
		src/commands_path.c\
		src/commands_data.c\
		src/commands_mode.c\
		src/commands_list.c\

OBJ	=	${SRC:.c=.o}

CFLAGS	=	-Wall -Werror -I include/

CC	=	gcc

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C tests clean

fclean: clean
	rm -f $(NAME)
	rm -f ${TESTS_NAME}
	make -C tests fclean

re: fclean
	make

unit_tests: re
	make -C tests
	cp tests/$(TESTS_NAME) .

tests_run: unit_tests
	./$(TESTS_NAME)

all:	$(NAME)

.PHONY: $(NAME) clean fclean re all unit_tests tests_run
