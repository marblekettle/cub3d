#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 13:17:49 by bmans         #+#    #+#                  #
#    Updated: 2020/02/13 09:44:38 by bmans         ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a
INCLUDE = ../
SRCSDIR = ./
SRCS = \
ft_printf.c	ft_print_resize.c ft_print_flags.c \
ft_itoa_prec.c ft_itoa_base_prec.c \
ft_print_char.c ft_print_string.c ft_print_ptr.c \
ft_print_int.c ft_print_uint.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft.a
LIBDIR = ../
CC = gcc
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o: $(addprefix $(SRCSDIR), %.c)
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

$(NAME): $(OBJS)
	mv $(LIBDIR)$(LIBFT) ./$(NAME)
	ar -rc $(NAME) $(OBJS)
	mv ./$(NAME) $(LIBDIR)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean
