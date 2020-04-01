/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/27 00:33:17 by brendan        #+#    #+#                */
/*   Updated: 2020/03/27 00:34:33 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

void		clear_texture(t_world *world, t_texture *texture)
{
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(world->mlx, texture->img);
		if (texture->name)
			free(texture->name);
		free(texture);
	}
}

void		clear_texture_list(t_world *world, t_list *lst)
{
	if (lst)
	{
		clear_texture_list(world, lst->next);
		clear_texture(world, (t_texture *)lst->content);
	}
}
