/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:28:24 by bmans          #+#    #+#                */
/*   Updated: 2020/03/05 14:30:19 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libftprintf.h"

int		main(void)
{
	t_world		*world;
	t_map		*map;

	world = world_init();
	if (world)
		ft_printf("World created successfully\n");
	if (!load_map("test.cub", &map))
		ft_printf("Map %s not loaded!\n", "test.cub");
	else
		ft_lstadd_back(&(world->l_textures), ft_lstnew(map));
	//world->window = mlx_new_window(world->mlx, 400, 400, "window");
	return (0);
}