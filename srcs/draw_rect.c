/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 16:23:49 by brendan        #+#    #+#                */
/*   Updated: 2020/03/20 12:15:35 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	draw_rect(int *coord, int color, t_world *world)
{
	int x;
	int y;

	y = coord[1];
	while (y <= coord[3])
	{
		x = coord[0];
		while (x <= coord[2])
		{
			mlx_pixel_put(world->mlx, world->window, x, y, color);
			x++;
		}
		y++;
	}
}
