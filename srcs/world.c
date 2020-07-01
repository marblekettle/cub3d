/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:15:37 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/01 14:25:30 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

void	lst_del(void *content)
{
	if (content)
		free(content);
}

void	world_end(t_world *world)
{
	if (world)
	{
		clear_texture_list(world, world->l_textures);
		ft_lstclear(&(world->l_objtypes), &lst_del);
		ft_lstclear(&(world->l_objs), &lst_del);
		ft_arrayclear(&(world->map->map));
		if (world->window)
			mlx_destroy_window(world->mlx, world->window);
		if (world->screen.img)
			mlx_destroy_image(world->mlx, world->screen.img);
	}
}

void	error_throw(const char *err, t_world *world, \
					void *tofree, const char *file)
{
	ft_printf_fd(2, "Error!\n");
	ft_printf_fd(2, err, file);
	ft_printf_fd(2, "\n");
	if (tofree != NULL)
		free(tofree);
	world_end(world);
	exit(0);
}

void	world_init(t_world *world)
{
	ft_bzero(world, sizeof(t_world));
	world->mlx = mlx_init();
	if (!world->mlx)
		error_throw("Could not initialize MiniLibX", world, NULL, NULL);
}
