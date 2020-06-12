/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:06:59 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/12 12:20:44 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_obj(t_objtype *objtype, int *pos, t_world *world)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	obj->type = objtype;
	(obj->pos)[0] = (double)pos[0] + 0.5;
	(obj->pos)[1] = (double)pos[1] + 0.5;
	ft_bzero(obj->dir, 32);
	ft_lstadd_back(&(world->l_objs), ft_lstnew(obj));
}
