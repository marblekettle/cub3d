/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 15:21:44 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/29 09:59:54 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	prepare_window(t_world *world, const char *name)
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
	world->screen.img = img;
	world->screen.width = dim[0];
	world->screen.height = dim[1];
	process_texture_data(&(world->screen), world);
}
