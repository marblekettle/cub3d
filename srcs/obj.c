/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:06:59 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/13 10:12:33 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	process_objs(t_map *map, t_world *world)
{
	int			**spotlist;
	t_list		*objlist;
	t_objtype	*type;
	int			i;

	objlist = world->l_objtypes;
	while (objlist)
	{
		type = (t_objtype *)(objlist->content);
		spotlist = ft_arraysearch(type->id, map->map);
		i = 0;
		while (spotlist[i])
		{
			new_obj(type, spotlist[i], world);
			i++;
		}
		ft_arrayclear((char ***)(&spotlist));
		objlist = objlist->next;
	}
}

void	process_sprite(const char *file, t_world *world)
{
	t_objtype	*type;
	t_texture	*sprite;
	t_list		*list;

	sprite = load_texture(world, file);
	type = malloc(sizeof(t_objtype));
	if (!type)
		error_throw("Out of memory", world, NULL, NULL);
	sprite->trans = TRANS_COLOR;
	type->id = '2';
	type->rad = fmax((double)(sprite->width) / (double)(sprite->height), 1.0);
	type->rad /= 2.0;
	type->sprite = sprite;
	list = ft_lstnew(type);
	if (!list)
		error_throw("Out of memory", world, type, NULL);
	ft_lstadd_back(&(world->l_objtypes), list);
}

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
