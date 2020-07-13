/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 10:28:15 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/13 11:17:41 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_bounds(t_world *world, double *move)
{
	int		spot[2];

	spot[0] = (int)(world->player.pos[0] + (sign(move[0]) * 0.2));
	spot[1] = (int)(world->player.pos[1] + (sign(move[1]) * 0.2));
	if (world->map->map[(int)(world->player.pos[1])][spot[0]] == '1')
		move[0] = 0.0;
	if (world->map->map[spot[1]][(int)(world->player.pos[0])] == '1')
		move[1] = 0.0;
	if (world->map->map[(int)(world->player.pos[1])][spot[0]] == '2')
		move[0] = 0.0;
	if (world->map->map[spot[1]][(int)(world->player.pos[0])] == '2')
		move[1] = 0.0;
}

void		move_player(t_world *world, char dir, double speed)
{
	double move[2];

	ft_bzero(move, 16);
	if (dir == '\03' || dir == '\04')
		speed = -speed;
	if (dir == '\01' || dir == '\03')
	{
		move[0] += world->player.dir[0] * speed;
		move[1] += world->player.dir[1] * speed;
	}
	if (dir == '\02' || dir == '\04')
	{
		move[0] += world->player.dir[1] * speed;
		move[1] -= world->player.dir[0] * speed;
	}
	check_bounds(world, move);
	world->player.pos[0] += move[0];
	world->player.pos[1] += move[1];
}
