/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_prefix.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 15:57:23 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/29 14:16:02 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static int		str_to_color(char *str, t_world *world, char *file)
{
	char	**split;
	int		rgb[3];

	split = ft_split(str, ',');
	if (!split)
		return (0);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	ft_arrayclear(&split);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		error_throw("Wrong color format", world, NULL, file);
	return (rgb[2] + (rgb[1] << 8) + (rgb[0] << 16));
}

static char		check_prefix_walltex(char **split, t_map *map, t_world *world)
{
	if (!ft_strncmp(split[0], "NO", 3) && ft_arraysize(split) == 2)
	{
		map->no_tex = load_texture(world, split[1]);
		return ('N');
	}
	else if (!ft_strncmp(split[0], "SO", 3) && ft_arraysize(split) == 2)
	{
		map->so_tex = load_texture(world, split[1]);
		return ('S');
	}
	else if (!ft_strncmp(split[0], "WE", 3) && ft_arraysize(split) == 2)
	{
		map->we_tex = load_texture(world, split[1]);
		return ('W');
	}
	else if (!ft_strncmp(split[0], "EA", 3) && ft_arraysize(split) == 2)
	{
		map->ea_tex = load_texture(world, split[1]);
		return ('E');
	}
	return (0);
}

static void		process_sprite(const char *file, t_world *world)
{
	t_objtype	*type;
	t_texture	*sprite;
	t_list		*list;
	char		*name;

	name = texture_name(file);
	if (!name)
		error_throw("Out of memory", world, NULL, NULL);
	list = ft_lstfind(name, world->l_textures);
	if (!list)
		sprite = load_texture(world, file);
	else
		sprite = (t_texture *)list->content;
	free(name);
	sprite->trans = 0xFFFF;
	type = malloc(sizeof(t_objtype));
	if (!type)
		error_throw("Out of memory", world, NULL, NULL);
	type->id = '2';
	type->rad = 0.5;
	type->sprite = sprite;
	list = ft_lstnew(type);
	if (!list)
		error_throw("Out of memory", world, type, NULL);
	ft_lstadd_back(&(world->l_objtypes), list);
}

static char		check_prefix_other(char **split, t_map *map, t_world *world, \
																char *file)
{
	if (!ft_strncmp(split[0], "R", 2) && ft_arraysize(split) == 3)
	{
		world->win_w = ft_atoi(split[1]);
		world->win_h = ft_atoi(split[2]);
		return ('R');
	}
	else if (!ft_strncmp(split[0], "F", 2) && ft_arraysize(split) == 2)
	{
		map->fl_color = str_to_color(split[1], world, file);
		return ('F');
	}
	else if (!ft_strncmp(split[0], "C", 2) && ft_arraysize(split) == 2)
	{
		map->cl_color = str_to_color(split[1], world, file);
		return ('C');
	}
	else if (!ft_strncmp(split[0], "S", 2) && ft_arraysize(split) == 2)
	{
		process_sprite(split[1], world);
		return ('s');
	}
	return (0);
}

char			check_prefix(char *str, t_map *map, t_world *world, char *file)
{
	char	**split;
	char	ret;

	split = ft_split(str, ' ');
	if (!split)
		error_throw("Out of memory", world, NULL, NULL);
	ret = check_prefix_walltex(split, map, world);
	if (!ret)
		ret = check_prefix_other(split, map, world, file);
	ft_arrayclear(&split);
	return (ret);
}
