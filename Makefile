# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburl <mburl@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 10:24:14 by mburl             #+#    #+#              #
#    Updated: 2019/10/18 11:12:33 by mburl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC := main.c
OBJ := $(SRC:.c=.o)

INCLUDE = /usr/local/include
LIB = /usr/local/lib -lmlx
LIBFT = libft/

FRAMEWORKS := -framework OpenGL -framework AppKit

CC := gcc
CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): lib $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) -I $(INCLUDE) -L $(LIB) -L. libft/libft.a $(FRAMEWORKS)

lib:
	make -C $(LIBFT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all