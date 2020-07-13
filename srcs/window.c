/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 15:21:44 by brendan       #+#    #+#                 */
/*   Updated: 2020/07/10 11:03:09 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	prepare_screen(t_world *world)
{
	t_texture	*screen;
	void		*img;
	int			page;

	page = 0;
	while (page < 2)
	{
		screen = malloc(sizeof(t_texture));
		if (!screen)
			error_throw("Out of memory", world, NULL, NULL);
		img = mlx_new_image(world->mlx, world->win_w, world->win_h);
		if (!img)
			error_throw("Could not create screen image", world, screen, NULL);
		world->screen[page] = screen;
		world->screen[page]->img = img;
		world->screen[page]->width = world->win_w;
		world->screen[page]->height = world->win_h;
		process_texture_data(world->screen[page], world);
		page++;
	}
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
