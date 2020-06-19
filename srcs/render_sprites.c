/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 12:54:35 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/19 13:19:31 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	obj_dist(t_world *world)
{
	t_list	*list;
	double	vec[4];

	list = world->l_objs;
	while (list)
	{
		ft_memcpy(vec, ((t_obj *)(list->content))->pos, 16);
		ft_memcpy(vec + 2, world->player->pos, 16);
		((t_obj *)(list->content))->dist = vec2_dist(vec, vec + 2);
		list = list->next;
	}
}