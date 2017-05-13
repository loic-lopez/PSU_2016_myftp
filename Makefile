##
## Makefile for makefile in /home/lopez_i/PSU_2016_myftp
##
## Made by Loic Lopez
## Login   <loic.lopez@epitech.eu>
##
## Started on  Mon Mar  6 10:06:57 2017 Loic Lopez
## Last update Sat Mar 11 15:16:26 2017 Loic Lopez
##

CC	=	gcc

RM	=	rm -rf

NAME	=	server

ECHO	=	/bin/echo -e

DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[5;31m"

CFLAGS	+=	-Wall -Werror -Wextra
CFLAGS	+=	-I./include/

SRC	=	src/main.c	\
		src/server.c	\
		src/utils.c


OBJS	=	$(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) && \
	$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(NAME) $(DEFAULT)  || \
	$(ECHO) $(RED) "[ERROR]" $(TEAL) $(OBJDUMP) $(DEFAULT)

clean	:
	@rm -f $(OBJS) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJS) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJS) $(DEFAULT)

fclean	:	clean
	@rm -f $(NAME) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(NAME) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(NAME) $(DEFAULT)

re	:	fclean all

.c.o:
		 @$(CC) $(CFLAGS) -c -o $@ $< && \
		 $(ECHO) $(GREEN) "[OK]" $(TEAL) $< "--->" $@ $(DEFAULT) || \
		 $(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)

.PHONY	:	all clean fclean re
