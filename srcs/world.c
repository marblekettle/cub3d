/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:15:37 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/17 14:10:40 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	lst_del(void *content)
{
	if (content)
		free(content);
}

void	world_end(void *world)
{
	t_world *world_ptr;

	if (world != NULL)
	{
		world_ptr = (t_world *)world;
		clear_texture_list(world_ptr, world_ptr->l_textures);
		ft_lstclear(&(world_ptr->l_objtypes), &lst_del);
		ft_lstclear(&(world_ptr->l_objs), &lst_del);
		ft_arrayclear(&(world_ptr->map->map));
		if (world_ptr->window)
			mlx_destroy_window(world_ptr->mlx, world_ptr->window);
		if (world_ptr->screen)
			clear_texture(world_ptr, world_ptr->screen);
		free(world_ptr);
	}
}

void	error_throw(const char *err, t_world *world, \
					void *tofree, const char *file)
{
	ft_printf_fd(2, "Error\n");
	ft_printf_fd(2, err, file);
	ft_printf_fd(2, "\n");
	if (tofree != NULL)
		free(tofree);
	world_end(world);
	exit(0);
}

t_world	*world_init(void)
{
	t_world *world;

	world = malloc(sizeof(t_world));
	if (!world)
		error_throw("Out of memory", world, NULL, NULL);
	else
	{
		ft_bzero(world, sizeof(t_world));
		world->mlx = mlx_init();
		if (!world->mlx)
			error_throw("Could not initialize MiniLibX", world, NULL, NULL);
	}
	return (world);
}
