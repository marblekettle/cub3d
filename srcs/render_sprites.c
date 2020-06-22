/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 12:54:35 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/22 15:23:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

void	obj_relpos(t_world *world)
{
	t_list	*list;
	double	vec[4];
	double	angle;

	list = world->l_objs;
	while (list)
	{
		vec[0] = ((t_obj *)(list->content))->pos[0] - world->player->pos[0];
		vec[1] = ((t_obj *)(list->content))->pos[1] - world->player->pos[1];
		angle = atan2(world->player->dir[1], world->player->dir[0]);
		vec2_rot(vec + 2, vec, 1.0, -angle);
		printf("%f %f\n", vec[2], vec[3]);
		ft_memcpy(((t_obj *)(list->content))->relpos, vec + 2, 16);
		list = list->next;
	}
	printf("\n");
}

void	sort_objs(t_world *world)
{

}
