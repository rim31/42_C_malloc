# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oseng <oseng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 13:53:42 by oseng             #+#    #+#              #
#    Updated: 2018/01/11 16:39:30 by oseng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so
FILES	= malloc.c ft_ft.c ft_malloc_tiny.c ft_malloc_small.c ft_free.c
SRCS	= $(addprefix src/, $(FILES))
OBJS	= $(SRCS:src/%.c=.obj/%.o)
INC	= -I include -I .

FLAGS	= -Wall -Wextra -Werror
CC	= gcc

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[96m by 🏀 seng\033[97m"
	@echo "\033[91mCompiling 😇\033[97m"
	@$(CC) -g -shared -o $(NAME) $(OBJS)
	@ln -s $(NAME) libft_malloc.so
	@echo "\033[90mDone 😎\033[97m"
.obj/%.o: src/%.c
	mkdir -p .obj
	@$(CC) -g -c $< -o $@ $(FLAGS) $(INC)

clean:
	@echo "\033[92mDeleting 💀\033[97m"
	@rm -rf .obj
	@echo "\033[96mClean done 😡\033[97m"

fclean: clean
	@echo "\033[92mDeleting 💀\033[97m"
	@rm -f $(NAME)
	@echo "\033[96mFclean Done 👿\033[97m"
	@rm -f libft_malloc.so libft_malloc_x86_64_Darwin.so

re: fclean all

.PHONY: all clean fclean re
