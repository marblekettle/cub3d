/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_rect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 16:23:49 by brendan        #+#    #+#                */
/*   Updated: 2020/03/22 02:30:41 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	draw_rect(int *ul_point, int *lr_point, int color, t_world *world)
{
	int x;
	int y;

	y = ul_point[1];
	while (y <= lr_point[1])
	{
		x = ul_point[0];
		while (x <= lr_point[0])
		{
			mlx_pixel_put(world->mlx, world->window, x, y, color);
			x++;
		}
		y++;
	}
}
