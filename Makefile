# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amazurie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/19 13:34:42 by amazurie          #+#    #+#              #
#    Updated: 2017/06/26 13:13:50 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

AUTOSTART = starting/autostart.sh

CC = gcc

CFLAGS = -Wall -Wextra -Werror

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
				$(SRC_HANDIN_PATH)/gest_in.c		\
				$(SRC_HANDIN_PATH)/hand_key.c		\
				$(SRC_HANDIN_PATH)/hand_key2.c		\
				$(SRC_HANDIN_PATH)/handle_hist.c	\
				$(SRC_HANDIN_PATH)/history.c		\
				$(SRC_HANDIN_PATH)/hand_arrow.c		\
				$(SRC_HANDIN_PATH)/hand_addel.c		\
				$(SRC_HANDIN_PATH)/quote.c			\
				$(SRC_HANDIN_PATH)/cursor.c

SRC_COMPLETE =	$(SRC_COMPL_PATH)/completion.c			\
				$(SRC_COMPL_PATH)/list_arg.c			\
				$(SRC_COMPL_PATH)/list_complcont.c		\
				$(SRC_COMPL_PATH)/complet_arg.c			\
				$(SRC_COMPL_PATH)/display_compl.c		\
				$(SRC_COMPL_PATH)/compldisplay_prep.c	\
				$(SRC_COMPL_PATH)/select.c				\
				$(SRC_COMPL_PATH)/check_size.c			\
				$(SRC_COMPL_PATH)/compl_star.c			\
				$(SRC_COMPL_PATH)/compl_color.c

OSRC = $(SRC:.c=.o) $(SRC_HANDIN:.c=.o) $(SRC_COMPLETE:.c=.o)

NO_COLOR = \x1b[0m#default: white
OK_COLOR = \x1b[32;01m#green
DEL_COLOR = \x1b[33m#yellow
ASCII_NAME = \x1b[0;36m#lightblue
WARN_COLOR = \x1b[31m#red

TOTAL_FILE = 38
SIZE_BAR = 2 #reduce number to reduce bar size

all: $(NAME)

$(NAME): $(LIB) $(OSRC)
	@echo "\nCompiling..."
	@$(CC) $(CFLAGS) $(OSRC) -o $@ -L $(LIB_PATH) -lft -lcurses
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"
	@echo "$(ASCII_NAME)"
	@cat starting/name
	@echo "$(NO_COLOR)"
	@echo "Thanks for testing my minishell !"
	@echo "$(WARN_COLOR)This is a simple shell like"
	@echo "Please, I try to learn."
	@echo "I'm not just an inconvenience you need to pass through even this is bothering you$(NO_COLOR)"
	@echo "minishell is ready to launch"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIB_INC_PATH) -I $(INC_PATH) -c -o $@ $?
	@$(eval compteur = $(shell echo $$(($(compteur)+1))))
	@$(eval total = $(shell echo ${compteur}*100 | bc))
	@$(eval total = $(shell echo ${total}/$(TOTAL_FILE) | bc))
	@$(eval bar = $(shell echo ${total}/$(SIZE_BAR) | bc))
	@echo "$(OK_COLOR)\r [ \c"
	@for ((i = 0; i < $(bar); ++i)); do echo "=\c"; done
	@for ((i = 0; i < $(shell echo 100/$(SIZE_BAR)-${bar} | bc); ++i)); do echo " \c"; done
	@echo "> ] $(total)%\c"
	@echo "$(NO_COLOR)\c"

clean:
	@make -C libft clean
	@/bin/rm -f $(OSRC)
	@echo "$(DEL_COLOR)Cleaning temporary files.$(NO_COLOR)"

fclean: clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)
	@echo "$(DEL_COLOR)Delete $(NAME) file.$(NO_COLOR)"

re: fclean all
