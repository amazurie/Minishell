# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amazurie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by amazurie          #+#    #+#              #
#    Updated: 2017/05/24 18:22:59 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

INC = includes

SRC = ft_itoa.c ft_memccpy.c ft_putchar_fd.c ft_strcat.c ft_striter.c		\
ft_strncmp.c ft_strsub.c ft_atoi.c ft_memchr.c ft_putendl.c ft_strchr.c		\
ft_striteri.c ft_strncpy.c ft_strtrim.c ft_bzero.c ft_memcmp.c				\
ft_putendl_fd.c ft_strclr.c ft_strjoin.c ft_strnequ.c ft_tolower.c			\
ft_isalnum.c ft_memcpy.c ft_putnbr.c ft_strcmp.c ft_strlcat.c ft_strnew.c	\
ft_toupper.c ft_isalpha.c ft_memdel.c ft_putnbr_fd.c ft_strcpy.c			\
ft_strlen.c ft_strnstr.c ft_isascii.c ft_memmove.c ft_putstr.c ft_strdel.c	\
ft_strmap.c ft_strrchr.c ft_isdigit.c ft_memset.c ft_putstr_fd.c			\
ft_strdup.c ft_strmapi.c ft_strsplit.c ft_isprint.c ft_memalloc.c			\
ft_putchar.c ft_strequ.c ft_strncat.c ft_strstr.c ft_lstnew.c				\
ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c				\
ft_isspace.c ft_isblank.c ft_isupper.c ft_islower.c ft_strndup.c			\
ft_strtrimc.c ft_strnjoin.c ft_strlen_chr.c ft_putnstr.c ft_putnchar.c		\
ft_lennb.c ft_putnbrbase.c ft_putwstr.c ft_lennbase.c ft_putwchar.c			\
ft_wstrlen.c ft_putnwstr.c ft_wstrnlen.c ft_itoa_base.c ft_strswap.c		\
ft_strschr.c ft_strschr_len.c ft_putnstr_fd.c ft_strcountc.c				\
ft_strisprint.c ft_lstcontdel.c get_next_line.c

FLAGS = -Wall -Wextra -Werror

OSRC = $(SRC:.c=.o)

HEADER = libft.h

NO_COLOR = \x1b[0m
OK_COLOR = \x1b[32;01m
DEL_COLOR = \x1b[33m

TOTAL_FILE = 85
SIZE_BAR = 2 #reduce number to reduce bar size

all: $(NAME)

$(NAME): $(OSRC)
	@echo "\nCompiling..."
	@ar rc $(NAME) $(OSRC)
	@ranlib $(NAME)
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"

%.o: %.c
	@$(CC) -o $@ $(FLAGS) -I $(INC) -c $<
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
	@rm -f $(OSRC)
	@echo "$(DEL_COLOR)Cleaning temporary files.$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(DEL_COLOR)Delete $(NAME) file.$(NO_COLOR)"

re: fclean all
