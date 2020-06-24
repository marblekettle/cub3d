/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 15:21:44 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/24 10:48:01 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void	prepare_screen(t_texture **screen, int *dim, t_world *world)
{
	void		*img;
	t_texture	*newscreen;

	img = mlx_new_image(world->mlx, dim[0], dim[1]);
	if (!img)
		error_throw("Could not create screen image", world, NULL, NULL);
	newscreen = malloc(sizeof(t_texture));
	if (!newscreen)
		error_throw("Out of memory", world, img, NULL);
	ft_bzero(newscreen, sizeof(t_texture));
	newscreen->img = img;
	newscreen->width = dim[0];
	newscreen->height = dim[1];
	process_texture_data(newscreen, world);
	*screen = newscreen;
}

void		prepare_window(t_world *world, const char *name)
{
	int		dim[2];
	char	i;

	dim[0] = world->win_w;
	dim[1] = world->win_h;
	world->window = mlx_new_window(world->mlx, dim[0], dim[1], (char *)name);
	if (!world->window)
		error_throw("Could not create window: %s", world, NULL, name);
	i = 0;
	while (i < 2)
	{
		prepare_screen(world->screen + i, dim, world);
		i++;
	}
}
