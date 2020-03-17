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

int		color_by_char(char c)
{
	if (c == '1')
		return (0xAA0000);
	if (c == '0')
		return (0x888888);
	if (c == '2')
		return (0x00AA00);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (0xDD);
	return (0x0);
}

void	draw_map(t_world *world, int dist)
{
	int		x;
	int		y;
	char	**map;
	int		coords[4];

	y = 0;
	map = world->map->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			coords[0] = (x * dist) + 1;
			coords[1] = (y * dist) + 1;
			coords[2] = ((x + 1) * dist) - 1;
			coords[3] = ((y + 1) * dist) - 1;
			draw_rect(coords, color_by_char(map[y][x]), world);
			x++;
		}
		y++;
	}
}

int		main(void)
{
	t_world		*world;
	t_map		*map;
	int			i;

	world = world_init();
	if (world)
		ft_printf("World created successfully\n");
	map = load_map("./test.cub", world);
	if (!map)
		ft_printf("Map %s not loaded!\n", "test.cub");
	ft_printf("%d, %d\n", world->win_width, world->win_height);
	i = 0;
	while (world->map->map[i] != NULL)
	{
		ft_printf("%s\n", world->map->map[i]);
		i++;
	}
	world->window = mlx_new_window(world->mlx, world->win_width, world->win_height, "window");
	draw_map(world, 25);
	mlx_loop(world->mlx);
	return (0);
}
