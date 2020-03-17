/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:20:58 by bmans          #+#    #+#                */
/*   Updated: 2020/03/17 18:06:04 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int		str_to_color(char *str)
{
	char	**split;
	int		rgb[3];

	split = ft_split(str, ',');
	if (!split)
		return (0);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
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

static char		check_prefix(char *str, t_map *map, t_world *world)
{
	char	**split;
	char	ret;

	ret = 0;
	split = ft_split(str, ' ');
	if (!ft_strncmp(split[0], "R", 2) && ft_arraysize(split) == 3)
	{
		world->win_width = ft_atoi(split[1]);
		world->win_height = ft_atoi(split[2]);
		ret = 'R';
	}
	else if (!ft_strncmp(split[0], "F", 2) && ft_arraysize(split) == 2)
	{
		map->fl_color = str_to_color(split[1]);
		ret = 'F';
	}
	else if (!ft_strncmp(split[0], "C", 2) && ft_arraysize(split) == 2)
	{
		map->cl_color = str_to_color(split[1]);
		ret = 'C';
	}
	else
		ret = check_prefix_walltex(split, map, world);
	ft_arrayclear(&split);
	return (ret);
}

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
	int i;
	int j;

	if (!map)
		return (0);
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

static void		parse_map_from_file(int fd, t_map *map, t_world *world)
{
	char *line;
	char ret;

	ret = 1;
	while (ret)
	{
		ret = (char)get_next_line(fd, &line);
		if (ret == -1)
			error_throw("File error", world, map);
		if (ft_strlen(line) > 0 && !check_prefix(line, map, world))
			ft_arraypush_back(&(map->map), line);
		if (ret >= 0)
			free(line);
	}
	if (!check_map(map->map))
		error_throw("Map contains invalid structure", world, map);
}

t_map			*load_map(char *file, t_world *world)
{
	t_map	*tmap;
	int		fd;

	tmap = malloc(sizeof(t_map));
	if (!tmap)
		error_throw("Out of memory", world, NULL);
	tmap->map = NULL;
	fd = open(file, O_RDWR);
	if (fd < 0)
		error_throw("File not found", world, tmap);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 5))
		error_throw("File not in .cub format", world, tmap);
	parse_map_from_file(fd, tmap, world);
	world->map = tmap;
	return (tmap);
}
