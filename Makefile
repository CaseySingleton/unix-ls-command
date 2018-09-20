# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csinglet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 18:59:57 by csinglet          #+#    #+#              #
#    Updated: 2018/08/08 20:49:18 by csinglet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ls

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
FLAGS			= $(CFLAGS) $(PFLAGS)

FILES			= error_checks.c file_info.c list_functions.c main.c \
				  manage_file.c manage_flags.c printing.c printing_2.c \
				  sorting.c time.c

SRC				= $(addprefix srcs/, $(FILES))
OBJ				= $(addprefix build/, $(FILES:.c=.o))

INC_LIBFT		= -I libft/includes
LINK_LIBFT		= -L libft -lft
FT				= $(INC_LIBFT) $(LINK_LIBFT)

all: $(NAME)

ft:
	@make -C libft
	@make re

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(FLAGS) $(FT) -I includes $(OBJ) -o $@

build:
	mkdir build

build/%.o: srcs/%.c | build
	@echo "Building $@"
	@$(CC) $(INC_LIBFT) -I includes -c $< -o $@

clean:
	@rm -fr build

fclean: clean
	@rm -f $(NAME)

re: fclean all
