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

char		parse_map_from_file(int fd, t_map *map, t_world *world)
{
	char *line;
	char ret;

	ret = 1;
	while (ret)
	{
		ret = (char)get_next_line(fd, &line);
		if (ret == -1)
			return (0);
		
	}
	return (1);
}

char		open_map(char *file, t_map *map, t_world *world)
{
	int fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		perror("Error: File not found\n");
		return (0);
	}
	if (!parse_map_from_file(fd, map, world))
	{
		perror("Error: Map parsing error");
		return (0);
	}
//	if (check_map(map))
//		return (0);
	return (1);
}

char		load_map(char *file, t_map **map, t_world *world)
{
	t_map *tmap;

	tmap = malloc(sizeof(t_map));
	if (!tmap)
	{
		perror("Error: Out of memory\n");
		return (0);
	}
	if (!open_map(tmap, file, world))
	{
		free(tmap);
		return (0);
	}
	*map = tmap;
	return (1);
}