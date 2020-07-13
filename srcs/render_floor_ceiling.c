/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_floor_ceiling.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 10:02:42 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/10 11:02:54 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>

void	render_floor_ceiling(t_world *world)
{
	int		pixel[2];
	size_t	spot;

	pixel[1] = 0;
	while (pixel[1] < world->win_h)
	{
		pixel[0] = 0;
		while (pixel[0] < world->win_w)
		{
			spot = pixel[0] + (world->screen[0]->linesize * pixel[1]);
			if (pixel[1] < world->win_h / 2)
				world->screen[0]->imgdata[spot] = world->map->cl_color;
			else
				world->screen[0]->imgdata[spot] = world->map->fl_color;
			pixel[0]++;
		}
		pixel[1]++;
	}
}
