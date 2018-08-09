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
		-Wunreachable-code -Iinclude/ -fno-stack-protector -fPIC

LFLAGS	=

NAME	=	utils

RM	=	rm -f

LN	=	ln -sf

BINDIR	=	bin

SRCDIR	=	src

SRC	=	utils_strreplace.c				\
		utils_strsplit.c				\
		utils_strjoin.c					\
		utils_wt_count.c				\
		utils_wt_pop_front.c				\
		utils_wt_push.c					\
		utils_wt_copy.c					\
		utils_wt_destroy.c				\
		utils_clearstr.c				\
		utils_perror.c					\
		utils_error.c					\
		utils_strsep.c

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
