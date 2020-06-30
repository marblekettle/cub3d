/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_am_not_doing_fractol_yet.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 09:17:08 by bmans          #+#    #+#                */
/*   Updated: 2020/03/06 09:59:11 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

int		is_in_fractal(double a, double b)
{
	int		rep;
	double	za;
	double	zb;
	double	t;

	rep = 1000;
	za = a;
	zb = b;
	while (rep > 0 && (za * za) + (zb * zb) < 2.0)
	{
		t = (za * za) - (zb * zb) + a;
		zb = (2.0 * za * zb) + b;
		za = t;
		rep--;
	}
	if ((za * za) + (zb * zb) < 2.0)
		return (0);
	else
		return (1);
}

int		color_fractal(int x, int y)
{
	double	a;
	double	b;
	int		ret;

	a = ((double)x / 400.0) - 2.0;
	b = ((double)y / 400.0) - 1.0;
	ret = is_in_fractal(a, b);
	if (ret == 0)
		return (0x0);
	else
		return (0x00FFFF);
}

int		main(void)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		col;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1200, 800, "I am not doing Fractol yet");
	y = 0;
	while (y < 800)
	{
		x = 0;
		while (x < 1200)
		{
			col = color_fractal(x, y);
			mlx_pixel_put(mlx, win, x, y, col);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
	return (0);
}
