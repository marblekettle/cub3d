/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:28:24 by bmans          #+#    #+#                */
/*   Updated: 2020/03/12 11:54:20 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libftprintf.h"

int		main(void)
{
	t_world		*world;
	t_map		*map;
	int			i;

	world = world_init();
	if (world)
		ft_printf("World created successfully\n");
	if (!load_map("./test.cub", &map, world))
		ft_printf("Map %s not loaded!\n", "test.cub");
	else
		ft_lstadd_back(&(world->l_textures), ft_lstnew(map));
	ft_printf("%d, %d\n", world->win_width, world->win_width);
	i = 0;
	while (map->map[i] != NULL)
	{
		ft_printf("%s\n", map->map[i]);
		i++;
	}
	world->window = mlx_new_window(world->mlx, world->win_width, world->win_height, "window");
	mlx_loop(world->mlx);
	return (0);
}
