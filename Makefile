# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburl <mburl@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 10:24:14 by mburl             #+#    #+#              #
#    Updated: 2020/03/12 11:40:09 by mburl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

# compiler
CC						=	gcc
CFLAGS					=	-Wall -Wextra -g
FRAMEWORK				:=	-framework OpenGL -framework AppKit

# directories
SRC_DIR					=	./srcs/
INC_DIR					=	./includes/
OBJ_DIR					=	./obj/

# src / obj files
SRC						:=	main.c terminate.c list_work.c win_work.c math.c drawing.c
# SRC						+=	 new_matrix.c matrix.c line.c
# SRC						+=	obj_transform.c  
OBJ						=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))

# HEADERS
HEADER_LIST				=	fdf.h
HEADERS					=	$(addprefix $(INC_DIR), $(HEADER_LIST))

# mlx library
MLX_LNK	= -lmlx 

# ft library
LIBFT_DIRECTORY			= ./libft/
FT_LIB					= $(LIBFT_DIRECTORY)/libft.a
FT_INC					= $(LIBFT_DIRECTORY)/includes/
FT_LNK					= -lft -L ./libft

#INCLUDE && LINK
INCLUDE					:=	-I $(FT_INC) -I $(INC_DIR)
LINK					:=	$(MLX_LNK) $(FT_LNK) $(FRAMEWORK)


all: $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADERS)
	@printf " \e[1;34m- Compiling  %-21s  ->  %-21s\n\e[m" "$<" "$@"
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) $(LINK) -o $@

clean:
	@echo " - Deleting $(OBJ_DIR)"
	@rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	@echo " - Deleting $(NAME)"
	@echo " - Cleaning $(LIBFT_DIRECTORY)"
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIRECTORY) fclean

re: fclean all