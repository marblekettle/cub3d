/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 10:28:15 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/29 10:28:32 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		move_player(t_world *world, char dir, double speed)
{
	if (dir == '\01')
	{
		world->player.pos[0] += world->player.dir[0] * speed;
		world->player.pos[1] += world->player.dir[1] * speed;
	}
	if (dir == '\03')
	{
		world->player.pos[0] -= world->player.dir[0] * speed;
		world->player.pos[1] -= world->player.dir[1] * speed;
	}
	if (dir == '\02')
	{
		world->player.pos[0] += world->player.dir[1] * speed;
		world->player.pos[1] -= world->player.dir[0] * speed;
	}
	if (dir == '\04')
	{
		world->player.pos[0] -= world->player.dir[1] * speed;
		world->player.pos[1] += world->player.dir[0] * speed;
	}
}
