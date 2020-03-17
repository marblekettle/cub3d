/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 16:23:49 by brendan        #+#    #+#                */
/*   Updated: 2020/03/17 16:23:52 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"
#include "mlx.h"

void	draw_rect(int *coords, int color, t_world *world)
{
	int x;
	int y;

	y = coords[1];
	while (y <= coords[3])
	{
		x = coords[0];
		while (x <= coords[2])
		{
			mlx_pixel_put(world->mlx, world->window, x, y, color);
			x++;
		}
		y++;
	}
}
