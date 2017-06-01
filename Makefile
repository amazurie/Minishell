# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by jmoucade          #+#    #+#              #
#    Updated: 2017/05/24 18:21:24 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

AUTOSTART = starting/autostart.sh

CC = gcc

CFLAGS = #-Wall -Wextra -Werror

INC_PATH = includes
SRC_PATH = srcs
SRC_HANDIN_PATH = $(SRC_PATH)/handin
SRC_COMPL_PATH = $(SRC_PATH)/completion
LIB_PATH = libft
LIB_INC_PATH = $(LIB_PATH)/includes
LIB = libft/libft.a

SRC =	$(SRC_PATH)/main.c			\
		$(SRC_PATH)/built_in.c		\
		$(SRC_PATH)/hand_env.c		\
		$(SRC_PATH)/hand_env2.c		\
		$(SRC_PATH)/extra.c			\
		$(SRC_PATH)/extra2.c		\
		$(SRC_PATH)/cd.c			\
		$(SRC_PATH)/cd2.c			\
		$(SRC_PATH)/env.c			\
		$(SRC_PATH)/env2.c			\
		$(SRC_PATH)/setenv.c		\
		$(SRC_PATH)/exec.c			\
		$(SRC_PATH)/echo.c			\
		$(SRC_PATH)/default_env.c	\
		$(SRC_PATH)/sig_handle.c	\
		$(SRC_PATH)/data.c			\
		$(SRC_PATH)/split.c			\
		$(SRC_PATH)/error.c

SRC_HANDIN =	$(SRC_HANDIN_PATH)/hand_in.c		\
				$(SRC_HANDIN_PATH)/hand_key.c		\
				$(SRC_HANDIN_PATH)/hand_key2.c		\
				$(SRC_HANDIN_PATH)/handle_hist.c	\
				$(SRC_HANDIN_PATH)/history.c		\
				$(SRC_HANDIN_PATH)/hand_arrow.c		\
				$(SRC_HANDIN_PATH)/quote.c			\
				$(SRC_HANDIN_PATH)/cursor.c

SRC_COMPLETE =	$(SRC_COMPL_PATH)/completion.c		\
				$(SRC_COMPL_PATH)/list_arg.c		\
				$(SRC_COMPL_PATH)/complet_arg.c		\
				$(SRC_COMPL_PATH)/display_compl.c	\
				$(SRC_COMPL_PATH)/select.c			\
				$(SRC_COMPL_PATH)/check_size.c		\
				$(SRC_COMPL_PATH)/compl_color.c

OSRC = $(SRC:.c=.o) $(SRC_HANDIN:.c=.o) $(SRC_COMPLETE:.c=.o)

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
DEL_COLOR=\x1b[33m

all: $(NAME) run

$(NAME): $(LIB) $(OSRC)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OSRC) -o $@ -L $(LIB_PATH) -lft -lcurses
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"
	@echo "running auto-starting"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIB_INC_PATH) -I $(INC_PATH) -c -o $@ $?

run: $(AUTOSTART)
	@sh $(AUTOSTART)

clean:
	@make -C libft clean
	@/bin/rm -f $(OSRC)
	@echo "$(DEL_COLOR)Cleaning temporary files.$(NO_COLOR)"

fclean: clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out
	@echo "$(DEL_COLOR)Delete $(NAME) file.$(NO_COLOR)"

re: fclean all
