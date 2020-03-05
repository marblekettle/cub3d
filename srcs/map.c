/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 14:20:58 by bmans          #+#    #+#                */
/*   Updated: 2020/03/05 14:34:17 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "cub3d.h"

char		parse_map(t_map *map, char *file)
{
	
}

char		load_map(char *file, t_map **map)
{
	t_map *tmap;

	tmap = malloc(sizeof(t_map));
	if (!tmap)
	{
		perror("Error: Out of memory\n");
		return (0);
	}
	if (!parse_map(tmap, file))
	{
		free(tmap);
		return (0);
	}
	*map = tmap;
	return (1);
}