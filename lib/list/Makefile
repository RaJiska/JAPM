##
## EPITECH PROJECT, 2018
## ftrace
## File description:
## ftrace
##

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Winit-self -Wwrite-strings \
		-Wcast-align -Wshadow -Wredundant-decls -Wfloat-equal \
		-Wundef -Wlogical-op -Winline -Wdouble-promotion \
		-Wunreachable-code -Iinclude/ -fno-stack-protector \
		-fdiagnostics-color

LFLAGS	=

NAME	=	list

RM	=	rm -f

LN	=	ln -sf

BINDIR	=	bin

SRCDIR	=	src

SRC	=	list_push.c				\
		list_count.c				\
		list_pop.c				\
		list_pop_by_elm.c			\
		list_get_by_elm.c			\
		list_destroy.c

SRC	:=	$(addprefix $(SRCDIR)/, $(SRC))

OBJ	=	$(SRC:.c=.o)

all:	lib$(NAME).a

lib$(NAME).a:	$(OBJ)
	$(AR) rvs lib$(NAME).a $(OBJ)
	$(LN) $(NAME)/lib$(NAME).a ../lib$(NAME).a

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) lib$(NAME).a
	$(RM) ../lib$(NAME).a

re:	fclean all

.PHONY:	all clean fclean re