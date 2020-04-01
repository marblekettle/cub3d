/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_maze.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 17:34:35 by brendan        #+#    #+#                */
/*   Updated: 2020/03/31 17:34:37 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

double	g_pi = 3.1415927;

void	shutdown(t_world *world)
{
	ft_printf("Shutting down...\n");
	world_end(world);
	exit(0);
}

int		key_hook(int keycode, void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	if (keycode == 53 || keycode == 65307)
		shutdown(world);
	if ((keycode == 123 || keycode == 65361))
		vec2_rot(world->player->dir, world->player->dir, 1.0, -0.05);
	if ((keycode == 124 || keycode == 65363))
		vec2_rot(world->player->dir, world->player->dir, 1.0, 0.05);
	if ((keycode == 125 || keycode == 65364))
	{
		world->player->pos[0] -= world->player->dir[0] * 0.05;
		world->player->pos[1] -= world->player->dir[1] * 0.05;
	}
	if ((keycode == 126 || keycode == 65362))
	{
		world->player->pos[0] += world->player->dir[0] * 0.05;
		world->player->pos[1] += world->player->dir[1] * 0.05;
	}
	render(world);
	return (0);
}

/* int		loop_hook(void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	vec2_rot(world->player->dir, world->player->dir, 1.0, 0.001);
	render(world);
} */

int		main(void)
{
	t_world	*world;
	t_map	*map;
	t_actor	*player;

	world = world_init();
	map = load_map("./test.cub", world);
//	printf("%s\n", world->map->so_tex->name);
	player = malloc(sizeof(t_actor));
	ft_memcpy(player->pos, world->map->init_pos, 16);
	ft_memcpy(player->dir, world->map->init_dir, 16);
	world->player = player;
	prepare_window(world, "window");
	render(world);
	mlx_hook(world->window, 2, 1L << 0, &key_hook, world);
//	mlx_loop_hook(world->mlx, &loop_hook, world);
	mlx_loop(world->mlx);
	return (0);
}