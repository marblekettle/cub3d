# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/27 14:49:12 by bmans         #+#    #+#                  #
#    Updated: 2020/07/03 14:18:44 by bmans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME_IN = 
NAME_OUT = cub3D
SRCS_DIR = srcs
HEADER_DIR = includes
HEADER_DIR_LINUX = minilibx/linux/include
HEADER_DIR_MACOS = minilibx/macos
LIB_DIR_LINUX = minilibx/linux
LIB_DIR_MACOS = .
LIB_DIR = libft
CC = gcc
FLAGS = -Wall -Wextra -Werror

libft:
	make -C $(LIB_DIR) all
	make -C $(LIB_DIR) clean

linux:
	gcc $(FLAGS) $(NAME_IN) $(SRCS_DIR)/*.c linux_compat.c -I$(HEADER_DIR) \
	-I$(HEADER_DIR_LINUX) -L$(LIB_DIR) -L$(LIB_DIR_LINUX) \
	-lft -lmlx -lm -lX11 -lXext -o $(NAME_OUT)

macos:
	gcc $(FLAGS) $(NAME_IN) $(SRCS_DIR)/*.c -I$(HEADER_DIR) \
	-I$(HEADER_DIR_MACOS) -L$(LIB_DIR) -L$(LIB_DIR_MACOS) \
	-lft -lmlx -o $(NAME_OUT) -g

clean:
	rm $(NAME_OUT)
	