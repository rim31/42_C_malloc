# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oseng <oseng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 18:13:45 by oseng             #+#    #+#              #
#    Updated: 2016/03/11 18:39:39 by oseng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GC = gcc

FLAG = -Wall -Wextra -Werror -I $(INCLUDE)

SRCS = 	ft_memset.c ft_strmap.c ft_putchar.c ft_strmapi.c ft_putchar_fd.c \
		ft_strncat.c ft_putendl.c ft_strncmp.c ft_putendl_fd.c ft_strncpy.c \
		ft_putnbr.c ft_strnequ.c ft_atoi.c ft_putnbr_fd.c ft_strnew.c \
		ft_bzero.c ft_putstr.c ft_strnstr.c ft_strclr.c ft_putstr_fd.c \
		ft_strrchr.c ft_isalnum.c ft_strcat.c ft_strsplit.c ft_isalpha.c \
		ft_strchr.c ft_strstr.c ft_isascii.c ft_strclr.c ft_strsub.c \
		ft_isdigit.c ft_strcmp.c ft_strtrim.c ft_isprint.c ft_strcpy.c \
		ft_tolower.c ft_itoa.c ft_strdel.c ft_toupper.c ft_memalloc.c \
		ft_strdup.c ft_memccpy.c ft_strequ.c ft_memchr.c ft_striter.c \
		ft_memcmp.c ft_striteri.c ft_memcpy.c ft_strjoin.c ft_memdel.c \
		ft_strlcat.c ft_memmove.c ft_strlen.c ft_strnequ.c ft_isblank.c \
		ft_toupper.c ft_sort_tab.c ft_isprime.c ft_lstadd.c ft_lstaddend.c \
		ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
		ft_islower.c ft_isupper.c get_next_line.c ft_itoa_base.c\

INCLUDE = libft.h

NAME = libft.a

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME):
		@echo "\033[42mLibrary\033[0m\c"
		@$(GC) $(SRCS) $(FLAG) -c
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:	fclean all
