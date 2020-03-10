# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 13:17:49 by bmans          #+#    #+#                 #
#    Updated: 2020/03/09 14:19:30 by bmans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INCLUDE = ../includes
SRCS = \
ft_atoi.c		ft_bzero.c		ft_calloc.c		ft_isalnum.c	ft_isalpha.c \
ft_isascii.c	ft_isdigit.c	ft_isprint.c	ft_itoa.c		ft_memccpy.c \
ft_memchr.c		ft_memcmp.c		ft_memcpy.c		ft_memmove.c	ft_memset.c \
ft_putchar_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c	ft_split.c \
ft_strchr.c		ft_strdup.c		ft_strjoin.c	ft_strlcat.c	ft_strlcpy.c \
ft_strlen.c		ft_strmapi.c	ft_strncmp.c	ft_strnstr.c	ft_strrchr.c \
ft_strtrim.c	ft_substr.c		ft_tolower.c	ft_toupper.c	\
ft_lstadd_back_bonus.c	ft_lstadd_front_bonus.c	ft_lstclear_bonus.c \
ft_lstdelone_bonus.c	ft_lstiter_bonus.c		ft_lstlast_bonus.c \
ft_lstmap_bonus.c		ft_lstnew_bonus.c		ft_lstsize_bonus.c \
ft_lstdel_plus.c	ft_lstpop_plus.c	ft_lstprint_plus.c	ft_iswhite_plus.c \
ft_putchar_plus.c	ft_putstr_plus.c	ft_putendl_plus.c	ft_putnbr_plus.c \
ft_putnchar_plus.c	ft_max_plus.c		ft_min_plus.c	\
ft_putnchar_fd_plus.c	gnl.c
OBJS = $(SRCS:.c=.o)
CC = gcc
FLAGS = -Wall -Werror -Wextra

all: $(NAME) printf

%.o: %.c
	$(CC) $(FLAGS) -c $< -I$(INCLUDE)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

printf: $(NAME)
	make all -C printf
	make clean -C printf
	mv libftprintf.a $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean