/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:39:09 by brendan       #+#    #+#                 */
/*   Updated: 2020/07/01 15:56:34 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"
#include "mlx.h"

void	save_screenshot(t_world *world)
{
	prepare_screen(world);
	render(world, 0);
	save_bitmap(&(world->screen), world, SCREENSHOT_NAME);
	ft_printf("Saved successfully as %s\n", SCREENSHOT_NAME);
}

void	start_world(t_world *world)
{
	prepare_window(world, WINDOW_TITLE);
	prepare_loop_hooks(world);
	render(world, 1);
	mlx_loop(world->mlx);
}

int		main(int ac, char **av)
{
	t_world	world;

	if (ac == 1 || (ac == 2 && !ft_strncmp("--save", av[1], 7)))
		ft_printf("Specify a .cub file to load\n");
	else if (ac == 2 || (ac == 3 && !ft_strncmp("--save", av[2], 7)))
	{
		world_init(&world);
		load_map(av[1], &world);
		ft_memcpy(world.player.pos, world.map->init_pos, 16);
		ft_memcpy(world.player.dir, world.map->init_dir, 16);
		if (ac == 3)
			save_screenshot(&world);
		else
			start_world(&world);
	}
	else
		ft_printf("Invalid arguments\n");
	return (0);
}
