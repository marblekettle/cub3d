/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 12:13:15 by brendan        #+#    #+#                */
/*   Updated: 2020/03/20 12:17:04 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static void	draw_line_pixels(int *coord, int *coef, int col, t_world *world)
{
	double	err;
	double	delta;
	char	vert;

	err = 0;
	vert = abs_int(coef[1]) > abs_int(coef[0]) ? 1 : 0;
	if (vert)
		delta = (double)(coef[0]) / (double)coef[1]; 
	else
		delta = (double)(coef[1]) / (double)coef[0];
	while (coord[0] != coord[2])
	{
		err += fabs(delta);
		if (err > 0.5)
		{
			coord[1] += (coord[1] < coord[3]) > 0 ? 1 : -1;
			err -= 1.0;
		}
		coord[0] += (coord[0] < coord[2]) > 0 ? 1 : -1;
		if (vert)
			mlx_pixel_put(world->mlx, world->window, coord[1], coord[0], col);
		else
			mlx_pixel_put(world->mlx, world->window, coord[0], coord[1], col);
	}
}

void		draw_line(int *coord, int color, t_world *world)
{
	int		tcoord[4];
	int		coef[2];

	mlx_pixel_put(world->mlx, world->window, coord[0], coord[1], color);
	if (coord[0] != coord[2] || coord[1] != coord[3])
	{
		ft_memcpy(tcoord, coord, 16);
		coef[0] = coord[2] - coord[0];
		coef[1] = coord[3] - coord[1];
		if (abs_int(coef[1]) > abs_int(coef[0]))
		{
			swap_int(tcoord, tcoord + 1);
			swap_int(tcoord + 2, tcoord + 3);
		}
		draw_line_pixels(tcoord, coef, color, world);
	}
}