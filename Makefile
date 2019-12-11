# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburl <mburl@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 10:24:14 by mburl             #+#    #+#              #
#    Updated: 2019/12/11 10:58:22 by mburl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

# src / obj files
SRC		= main.c list_work.c printer.c drawing.c math.c new_matrix.c matrix.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -g

# mlx library
MLX		= ./miniLibX/
MLX_INC	= -I ./miniLibX
MLX_LNK	= -L ./miniLibX -l mlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) -g $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(NAME): $(OBJ)
	$(CC) -g $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all