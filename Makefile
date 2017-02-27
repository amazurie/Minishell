# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by jmoucade          #+#    #+#              #
#    Updated: 2017/02/27 16:29:31 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = #-Wall -Wextra -Werror

INC_PATH = includes
SRC_PATH = srcs
LIB_PATH = libft
LIB_INC_PATH = $(LIB_PATH)/includes
LIB = libft/libft.a

SRC =	$(SRC_PATH)/main.c			\
		$(SRC_PATH)/hand_env.c		\
		$(SRC_PATH)/handle_hist.c	\
		$(SRC_PATH)/history.c		\
		$(SRC_PATH)/exec.c

OSRC = $(SRC:.c=.o)

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m

all: $(NAME)

$(NAME): $(LIB) $(OSRC)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OSRC) -o $@ -L $(LIB_PATH) -lft
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIB_INC_PATH) -I $(INC_PATH) -c -o $@ $?
	@echo "Linking file $@"

clean:
	@make -C libft clean
	@/bin/rm -f $(OSRC)
	@echo "Cleaning temporary files."

fclean: clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out
	@echo "Delete $(NAME) file."

re: fclean all
