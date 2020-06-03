/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 15:21:44 by brendan        #+#    #+#                */
/*   Updated: 2020/06/03 10:03:58 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void		prepare_window(t_world *world, const char *name)
{
	int		dim[2];
	void	*img;

	dim[0] = world->win_w;
	dim[1] = world->win_h;
	world->window = mlx_new_window(world->mlx, dim[0], dim[1], (char *)name);
	if (!world->window)
		error_throw("Could not create window: %s", world, NULL, name);
	img = mlx_new_image(world->mlx, dim[0], dim[1]);
	if (!img)
		error_throw("Could not create screen image", world, NULL, NULL);
	world->screen = malloc(sizeof(t_texture));
	if (!world->screen)
		error_throw("Out of memory", world, img, NULL);
	ft_bzero(world->screen, sizeof(t_texture));
	world->screen->img = img;
	process_texture_data(world->screen, world);
}
