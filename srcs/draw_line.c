/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 12:13:15 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/17 14:05:23 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static void	draw_line_pixels(int *point, int *coef, int col, t_world *world)
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
	while (point[0] != point[2])
	{
		err += fabs(delta);
		if (err > 0.5)
		{
			point[1] += (point[1] < point[3]) > 0 ? 1 : -1;
			err -= 1.0;
		}
		point[0] += (point[0] < point[2]) > 0 ? 1 : -1;
		if (vert)
			mlx_pixel_put(world->mlx, world->window, point[1], point[0], col);
		else
			mlx_pixel_put(world->mlx, world->window, point[0], point[1], col);
	}
}

void		draw_line(int *s_point, int *e_point, int color, t_world *world)
{
	int		tpoint[4];
	int		coef[2];

	mlx_pixel_put(world->mlx, world->window, s_point[0], s_point[1], color);
	if (s_point[0] != e_point[0] || s_point[1] != e_point[1])
	{
		ft_memcpy(tpoint, s_point, 8);
		ft_memcpy(tpoint + 2, e_point, 8);
		coef[0] = e_point[0] - s_point[0];
		coef[1] = e_point[1] - s_point[1];
		if (abs_int(coef[1]) > abs_int(coef[0]))
		{
			swap_int(tpoint, tpoint + 1);
			swap_int(tpoint + 2, tpoint + 3);
		}
		draw_line_pixels(tpoint, coef, color, world);
	}
}
