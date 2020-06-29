/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/26 15:26:00 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/26 16:46:24 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static int	shutdown(void *world_ptr)
{
	ft_printf("Shutting down...\n");
	world_end((t_world *)world_ptr);
	exit(0);
}

static int	key_press_hook(int keycode, void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	if (keycode == 53 || keycode == 65307)
		shutdown(world);
	if (keycode == 126 || keycode == 65362 || keycode == 119)
		world->control.keypress |= '\01';
	if (keycode == 125 || keycode == 65364 || keycode == 115)
		world->control.keypress |= '\02';
	if (keycode == 123 || keycode == 65361)
		world->control.keypress |= '\04';
	if (keycode == 124 || keycode == 65363)
		world->control.keypress |= '\010';
	if (keycode == 97)
		world->control.keypress |= '\020';
	if (keycode == 100)
		world->control.keypress |= '\040';
	return (0);
}

static int	key_release_hook(int keycode, void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	if (keycode == 126 || keycode == 65362 || keycode == 119)
		world->control.keypress &= ~'\01';
	if (keycode == 125 || keycode == 65364 || keycode == 115)
		world->control.keypress &= ~'\02';
	if (keycode == 123 || keycode == 65361)
		world->control.keypress &= ~'\04';
	if (keycode == 124 || keycode == 65363)
		world->control.keypress &= ~'\010';
	if (keycode == 97)
		world->control.keypress &= ~'\020';
	if (keycode == 100)
		world->control.keypress &= ~'\040';
	return (0);
}

static int	loop_hook(void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	if (world->control.keypress & '\01')
	{
		world->player.pos[0] += world->player.dir[0] * 0.05;
		world->player.pos[1] += world->player.dir[1] * 0.05;
	}
	if (world->control.keypress & '\02')
	{
		world->player.pos[0] -= world->player.dir[0] * 0.05;
		world->player.pos[1] -= world->player.dir[1] * 0.05;
	}
	if (world->control.keypress & '\04')
	{
		vec2_rot(world->player.dir, world->player.dir, 1.0, -0.05);
	}
	if (world->control.keypress & '\010')
	{
		vec2_rot(world->player.dir, world->player.dir, 1.0, 0.05);
	}
	if (world->control.keypress & '\020')
	{
		world->player.pos[0] += world->player.dir[1] * 0.05;
		world->player.pos[1] -= world->player.dir[0] * 0.05;
	}
	if (world->control.keypress & '\040')
	{
		world->player.pos[0] -= world->player.dir[1] * 0.05;
		world->player.pos[1] += world->player.dir[0] * 0.05;
	}
	render(world);
	return (0);
}

void		prepare_loop_hooks(t_world *world)
{
	mlx_hook(world->window, 2, 1L, &key_press_hook, world);
	mlx_hook(world->window, 3, 1L << 1, &key_release_hook, world);
	mlx_hook(world->window, 17, 0L, &shutdown, world);
	mlx_loop_hook(world->mlx, &loop_hook, world);
}