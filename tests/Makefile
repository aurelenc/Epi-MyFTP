##
## EPITECH PROJECT, 2022
## MyFTP
## File description:
## Makefile
##

NAME	=	unit_tests

SRC	=	../src/my_ftp.c\

TEST_SRC	=	tests_my_ftp.c

CFLAGS	=	-Wall -Werror

LDFLAGS = -lpthread -lcriterion --coverage -I ../include/

$(NAME):
	gcc $(SRC) $(TEST_SRC) -o $(NAME) ${LDFLAGS}

clean:
	rm -f *.gc*

fclean: clean
	rm -f $(NAME)

all:	$(NAME)

.PHONY: $(NAME) clean fclean all
