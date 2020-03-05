/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:15:37 by bmans          #+#    #+#                */
/*   Updated: 2020/03/05 12:01:58 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	world_end(void *world)
{
	t_world *world_ptr;

	world_ptr = (t_world *)world;
	ft_lstclear(&(world_ptr->l_textures), &clear_texture);
	free(world_ptr->l_textures);
	mlx_destroy_window(world_ptr->mlx, world_ptr->window);
	free(world);
}

t_world	*world_init(void)
{
	t_world *world;

	world = malloc(sizeof(t_world));
	if (!world)
		perror("Error: Out of memory\n");
	else
	{
		ft_memset(world, 0, sizeof(t_world));
		world->mlx = mlx_init();
		if (!world->mlx)
		{
			perror("Error: Could not initialize MiniLibX\n");
			free(world);
			world = NULL;
		}
	}
	return (world);
}
