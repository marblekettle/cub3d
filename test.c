/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 16:20:02 by bmans         #+#    #+#                 */
/*   Updated: 2020/02/27 16:21:34 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/macos/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* 
** mlx_init, mlx_new_window
** mlx_clear_window, mlx_pixel_put
** mlx_new_image, mlx_get_data_addr
** mlx_put_image_to_window, mlx_get_color_value
** mlx_moise_hook, mlx_key_hook
** mlx_loop_hook, mlx_expose_hook
** mlx_loop, mlx_string_put
** mlx_xpm_to_image, mlx_xpm_file_to_image
** mlx_png_file_to_image, mlx_destroy_window
** mlx_destroy_image, mlx_hook
** mlx_mouse_hide, mlx_mouse_show
** mlx_mouse_move, mlx_mouse_get_pos
** mlx_do_key_autorepeatoff, mlx_do_key_autorepeaton
** mlx_do_sync, mlx_sync
*/ 

int		whitenoise(void **params)
{
	static unsigned int	x = 0;
	static unsigned int	y = 0;
	void				*mlx;
	void				*win;

	mlx = params[0];
	win = params[1];
	printf("%p %p\n", mlx, win);
	fflush(0);
	printf("%u %u\n", x, y);
	for (int i = 0; i < 10; i++)
	{
		mlx_pixel_put(mlx, win, (int)x, (int)y, 0x00FFFFFF);
		x = ((x + 1) % 64);
		y = ((y + 1) % 48);
	}
	printf(":D\n");
	fflush(0);
	return (0);
}

int		test(int *a)
{
	for (int i = 0; i < 5; i++)
		printf("%d\n", a[i]);
	fflush(0);
	sleep(1000);
	return (0);
}

int		main(void)
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*params[2];
	int		dim[5] = {235, 235, 0, 0, 0};
	char	*imgstr;
	unsigned int *colorstr;

	mlx = mlx_init();
	if (mlx)
	{
		printf(":D\n");
		fflush(0);
		win = mlx_new_window(mlx, dim[0], dim[1], "win");
		params[0] = mlx;
		params[1] = win;
		mlx_clear_window(mlx, win);
		img = mlx_png_file_to_image(mlx, "mick.png", &dim[0], &dim[1]);
		if (img)
		{
			imgstr = mlx_get_data_addr(img, &dim[2], &dim[3], &dim[4]);
			colorstr = (unsigned int *)imgstr;
			printf("%d\n", dim[2]);
			printf("%d\n", dim[3]);
			printf("%d\n", dim[4]);
			for (int j = 0; j < 235; j++)
			{
				for (int i = 0; i < 235; i++)
					mlx_pixel_put(mlx, win, i / 5 + 20, j / 3 + 20, colorstr[i + dim[3]/4 * j]);
			}
			mlx_loop(mlx);
		}
		else
			perror(strerror(errno));
	}
	else
	{
		printf(":|");
		fflush(0);
	}
	return (0);
}
