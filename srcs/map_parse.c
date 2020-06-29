/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:20:58 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/29 14:14:51 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static void		parse_file(int fd, t_map *map, \
							t_world *world, char *file)
{
	char *line;
	char ret;

	ret = 1;
	while (ret)
	{
		ret = (char)get_next_line(fd, &line);
		if (ret == -1)
			error_throw("File error: %s", world, map, file);
		if (ft_strlen(line) > 0 && !check_prefix(line, map, world, file))
		{
			while (ret || *line)
			{
				ft_arraypush_back(&(map->map), line);
				free(line);
				ret = (char)get_next_line(fd, &line);
			}
		}
		free(line);
	}
	if (!map->map)
		error_throw("Map error: %s", world, NULL, file);
	if (!check_map(map->map))
		error_throw("Invalid map layou: %s", world, NULL, file);
}

static void		process_objs(t_map *map, t_world *world)
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

static void		process_map(t_map *map, t_world *world)
{
	int		spot[2];
	char	found;

	found = ft_arrayfind(spot, "NSWE", map->map);
	if (!found)
		error_throw("No player start", world, map, NULL);
	else
	{
		map->init_pos[0] = (double)spot[0] + 0.5;
		map->init_pos[1] = (double)spot[1] + 0.5;
		ft_bzero(map->init_dir, 16);
		if (found == 'N' || found == 'S')
			map->init_dir[1] = (found == 'S') ? 1.0 : -1.0;
		if (found == 'E' || found == 'W')
			map->init_dir[0] = (found == 'E') ? 1.0 : -1.0;
	}
	process_objs(map, world);
}

t_map			*load_map(char *file, t_world *world)
{
	t_map	*tmap;
	int		fd;

	tmap = malloc(sizeof(t_map));
	if (!tmap)
		error_throw("Out of memory", world, NULL, NULL);
	tmap->map = NULL;
	fd = open(file, O_RDWR);
	if (fd < 0)
		error_throw("File not found: %s", world, tmap, file);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 5))
		error_throw("File not in .cub format: %s", world, tmap, file);
	parse_file(fd, tmap, world, file);
	process_map(tmap, world);
	world->map = tmap;
	return (tmap);
}
