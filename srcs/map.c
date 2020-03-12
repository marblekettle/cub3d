/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:20:58 by bmans          #+#    #+#                */
/*   Updated: 2020/03/09 14:41:03 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static char		check_prefix()
{

}

static char		parse_map_from_file(int fd, t_map *map, t_world *world)
{
	char *line;
	char ret;

	ret = 1;
	while (ret)
	{
		ret = (char)get_next_line(fd, &line);
		if (ret == -1)
			return (0);
		if (!check_prefix(line))
			ft_arraypush_back(&(map.map), line);
		if (ret >= 0)
			free(line);
	}
	if (!check_map(map.map))
	{
		ft_arrayclear(map.map);
		map.map = NULL;
		return (0);
	}
	return (1);
}

char			load_map(char *file, t_map **map, t_world *world)
{
	t_map	*tmap;
	int		fd;

	tmap = malloc(sizeof(t_map));
	if (!tmap)
	{
		perror("Error: Out of memory\n");
		return (0);
	}
	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		free(tmap);
		perror("Error: File not found\n");
		return (0);
	}
	if (!parse_map_from_file(fd, tmap, world))
	{
		perror("Error: Map parsing error\n");
		return (0);
	}
	*map = tmap;
	return (1);
}
