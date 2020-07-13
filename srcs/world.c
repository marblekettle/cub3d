/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   world.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:15:37 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/13 09:57:35 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

static void	lst_del(void *content)
{
	if (content)
		free(content);
}

static void	config_clear(t_world *world)
{
	if (world->config.config_file)
		ft_arrayclear(&(world->config.config_file));
	if (world->config.path_no)
		free(world->config.path_no);
	if (world->config.path_so)
		free(world->config.path_so);
	if (world->config.path_we)
		free(world->config.path_we);
	if (world->config.path_ea)
		free(world->config.path_ea);
	if (world->config.path_s)
		free(world->config.path_s);
}

void		world_end(t_world *world)
{
	int	page;

	if (world)
	{
		clear_texture_list(world, world->l_textures);
		ft_lstclear(&(world->l_objtypes), &lst_del);
		ft_lstclear(&(world->l_objs), &lst_del);
		config_clear(world);
		ft_arrayclear(&(world->map->map));
		if (world->map)
			free(world->map);
		if (world->window)
			mlx_destroy_window(world->mlx, world->window);
		page = 0;
		while (page < 2)
		{
			if (world->screen[page])
			{
				if (world->screen[page]->img)
					mlx_destroy_image(world->mlx, world->screen[page]->img);
				free(world->screen[page]);
			}
			page++;
		}
	}
}

void		error_throw(const char *err, t_world *world, \
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

void		world_init(t_world *world)
{
	ft_bzero(world, sizeof(t_world));
	world->mlx = mlx_init();
	if (!world->mlx)
		error_throw("Could not initialize MiniLibX", world, NULL, NULL);
}
