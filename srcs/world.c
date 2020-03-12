/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:15:37 by bmans          #+#    #+#                */
/*   Updated: 2020/03/12 14:48:36 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	world_end(void *world)
{
	t_world *world_ptr;

	if (world != NULL)
	{
		world_ptr = (t_world *)world;
		ft_lstclear(&(world_ptr->l_textures), &clear_texture);
		ft_arrayclear(&(world_ptr->map->map));
		mlx_destroy_window(world_ptr->mlx, world_ptr->window);
		free(world);
	}
}

void	error_throw(char *err_message, t_world *world, void **tofree)
{
	perror(err_message);
	if (tofree != NULL)
		free(tofree);
	world_end(world);
	while (1) {};
	exit(0);
}

t_world	*world_init(void)
{
	t_world *world;

	world = malloc(sizeof(t_world));
	if (!world)
		error_throw("Error\nOut of memory\n", world, NULL);
	else
	{
		ft_memset(world, 0, sizeof(t_world));
		world->mlx = mlx_init();
		if (!world->mlx)
			error_throw("Error\nCould not initialize MiniLibX\n", world, NULL);
	}
	return (world);
}
