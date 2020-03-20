# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/27 14:49:12 by bmans          #+#    #+#                 #
#    Updated: 2020/03/20 12:16:47 by brendan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME_IN = test_map.c
NAME_OUT = a.out
SRCS_DIR = srcs
HEADER_DIR = includes
HEADER_DIR_LINUX = minilibx/linux/include
HEADER_DIR_MACOS = minilibx/macos
LIB_DIR_LINUX = minilibx/linux
LIB_DIR_MACOS = minilibx/macos
LIB_DIR = libft
CC = gcc

libft:
	make -C $(LIB_DIR)
	make -C $(LIB_DIR) clean

linux:
	gcc $(NAME_IN) $(SRCS_DIR)/*.c -I$(HEADER_DIR) -I$(HEADER_DIR_LINUX) \
	-L$(LIB_DIR) -L$(LIB_DIR_LINUX) -lft -lmlx -lm -lX11 -lXext -o $(NAME_OUT) -g

macos:
	gcc $(NAME_IN) $(SRCS_DIR)/*.c -I$(HEADER_DIR) -I$(HEADER_DIR_MACOS) \
	-L$(LIB_DIR) -L$(LIB_DIR_MACOS) -lft -lmlx -o $(NAME_OUT)

clean:
	rm $(NAME_OUT)
