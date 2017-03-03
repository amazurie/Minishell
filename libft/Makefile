# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amazurie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by amazurie          #+#    #+#              #
#    Updated: 2017/03/03 14:10:09 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

SRC = ft_itoa.c ft_memccpy.c ft_putchar_fd.c ft_strcat.c ft_striter.c \
ft_strncmp.c ft_strsub.c ft_atoi.c ft_memchr.c ft_putendl.c ft_strchr.c \
ft_striteri.c ft_strncpy.c ft_strtrim.c ft_bzero.c ft_memcmp.c ft_putendl_fd.c \
ft_strclr.c ft_strjoin.c ft_strnequ.c ft_tolower.c ft_isalnum.c ft_memcpy.c \
ft_putnbr.c ft_strcmp.c ft_strlcat.c ft_strnew.c ft_toupper.c ft_isalpha.c \
ft_memdel.c ft_putnbr_fd.c ft_strcpy.c ft_strlen.c ft_strnstr.c ft_isascii.c \
ft_memmove.c ft_putstr.c ft_strdel.c ft_strmap.c ft_strrchr.c ft_isdigit.c \
ft_memset.c ft_putstr_fd.c ft_strdup.c ft_strmapi.c ft_strsplit.c ft_isprint.c \
ft_memalloc.c ft_putchar.c ft_strequ.c ft_strncat.c ft_strstr.c ft_lstnew.c \
ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_isspace.c \
ft_isblank.c ft_isupper.c ft_islower.c ft_strndup.c ft_strtrimc.c ft_strnjoin.c \
ft_strlen_chr.c ft_putnstr.c ft_putnchar.c ft_lennb.c ft_putnbrbase.c ft_putwstr.c \
ft_lennbase.c ft_putwchar.c ft_wstrlen.c ft_putnwstr.c ft_wstrnlen.c ft_itoa_base.c \
ft_strswap.c get_next_line.c ft_strschr.c ft_strschr_len.c

FLAGS = -Wall -Wextra -Werror

OSRC = $(SRC:.c=.o)

HEADER = libft.h

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m

all: $(NAME)

$(NAME):
	@echo "Compiling..."
	$(CC) $(FLAGS) -c $(SRC) -I includes
	ar rc $(NAME) $(OSRC)
	ranlib $(NAME)
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"

%.o: %.c
	$(CC) -o $@ $(FLAGS) -c $<
	@echo "Linking file $@"

clean:
	-rm -f $(OSRC)
	@echo "Cleaning temporary files."

fclean: clean
	-rm -f $(NAME)
	@echo "Delete $(NAME) file."

re: fclean all
