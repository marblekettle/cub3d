/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 15:21:44 by brendan       #+#    #+#                 */
/*   Updated: 2020/07/01 15:54:20 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	prepare_screen(t_world *world)
{
	void	*img;

	img = mlx_new_image(world->mlx, world->win_w, world->win_h);
	if (!img)
		error_throw("Could not create screen image", world, NULL, NULL);
	world->screen.img = img;
	world->screen.width = world->win_w;
	world->screen.height = world->win_h;
	process_texture_data(&(world->screen), world);
}

void	prepare_window(t_world *world, const char *name)
{
	int		dim[2];

	mlx_get_screen_size(world->mlx, dim, dim + 1);
	if (dim[0] < world->win_w)
		world->win_w = dim[0];
	if (dim[1] < world->win_h)
		world->win_h = dim[1];
	dim[0] = world->win_w;
	dim[1] = world->win_h;
	world->window = mlx_new_window(world->mlx, dim[0], dim[1], (char *)name);
	if (!world->window)
		error_throw("Could not create window: %s", world, NULL, name);
	prepare_screen(world);
}
