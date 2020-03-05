make -C libft && make -C libft clean && gcc -Wall -Wextra -Werror test_simpleimage.c srcs/* -Iincludes -L. -Llibft -lmlx -lft
