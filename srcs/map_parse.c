/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:20:58 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/10 15:37:50 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static char		check_spot(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[j + 1])
		return (0);
	if (!map[j][i + 1] || map[j][i + 1] == ' ')
		return (0);
	if (!map[j][i - 1] || map[j][i - 1] == ' ')
		return (0);
	if (ft_strlen(map[j - 1]) <= i || ft_strlen(map[j + 1]) <= i)
		return (0);
	if (!map[j + 1][i] || map[j + 1][i] == ' ')
		return (0);
	if (!map[j - 1][i] || map[j - 1][i] == ' ')
		return (0);
	if (!map[j + 1][i + 1] || map[j + 1][i + 1] == ' ')
		return (0);
	if (!map[j - 1][i + 1] || map[j - 1][i + 1] == ' ')
		return (0);
	if (!map[j + 1][i - 1] || map[j + 1][i - 1] == ' ')
		return (0);
	if (!map[j - 1][i - 1] || map[j - 1][i - 1] == ' ')
		return (0);
	return (1);
}

static char		check_map(char **map)
{
	int		i;
	int		j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] != ' ' && map[j][i] != '1')
			{
				if (!check_spot(map, i, j))
					return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

static void		parse_file(int fd, t_map *map, \
							t_world *world, const char *file)
{
	char *line;
	char ret;

	ret = 1;
	while (ret)
	{
		ret = (char)get_next_line(fd, &line);
		if (ret == -1)
			error_throw("File error: %s", world, map, file);
		if (ft_strlen(line) > 0 && !check_prefix(line, map, world))
		{
			while (ret || *line)
			{
				ft_arraypush_back(&(map->map), line);
				free(line);
				ret = (char)get_next_line(fd, &line);
			}
			break ;
		}
		free(line);
	}
	if (!map->map)
		error_throw("Map error", world, map, NULL);
	if (!check_map(map->map))
		error_throw("Invalid map layout", world, map, NULL);
}

static void		process_objs(t_map *map, t_world *world)
{
	int		spot[2];
	t_list	*objlist;

	ft_bzero(spot, 8);
	while ((map->map)[spot[1]])
	{
		while ((map->map)[spot[0]])
		{
			if (!ft_strchr(" 01NSWE", (map->map)[spot[1]][spot[0]]))
			{
				objlist = world->l_objtypes;
				while (objlist)
				{
					if ((t_objtype *)(objlist->content)
						
				}
			}
			spot[0]++;
		}
		spot[1]++;
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
