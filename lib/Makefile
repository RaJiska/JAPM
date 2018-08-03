##
## EPITECH PROJECT, 2018
## ftrace
## File description:
## ftrace
##

LIBS	=	utils			\
		list

all:
	@for i in $(LIBS); do \
		$(MAKE) -C $$i/ ; \
	done

clean:
	@for i in $(LIBS); do \
		$(MAKE) -C $$i/ clean ; \
	done

fclean:
	@for i in $(LIBS); do \
		$(MAKE) -C $$i/ fclean ; \
	done

re:	clean
	@for i in $(LIBS); do \
		$(MAKE) -C $$i/ re ; \
	done

.PHONY:	all clean fclean re