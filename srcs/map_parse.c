/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 10:20:05 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/13 10:12:39 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include "libftprintf.h"

char	*g_prefixlist[8] = {"NO ", "EA ", "SO ", "WE ", "S ", "R ", "F ", "C "};

static char	**parse_file(int fd, t_world *world, char *file)
{
	char	**arr;
	char	*line;
	char	ret;

	ret = 1;
	arr = NULL;
	line = NULL;
	while (ret)
	{
		ret = (char)get_next_line(fd, &line);
		if (ret == -1 || !line)
		{
			ft_arrayclear(&arr);
			error_throw("File error: %s", world, NULL, file);
		}
		ft_arraypush_back(&arr, line);
		free(line);
	}
	return (arr);
}

static char	get_prefix_type(char *line, char *file, t_world *world)
{
	size_t	i;
	char	set;

	i = 0;
	set = 1;
	while (i < 8)
	{
		if (!ft_strncmp(line, g_prefixlist[i], ft_strlen(g_prefixlist[i]) - 1))
		{
			if (world->config.set & set)
				error_throw("Duplcate config line: %s", world, NULL, file);
			world->config.set += set;
			config_action(i, line + 2, world);
			break ;
		}
		i++;
		set = set << 1;
	}
	return (("NESWsRFC")[i]);
}

static void	check_cub_content(char **arr, char *file, t_world *world)
{
	size_t	i;
	char	type;

	i = 0;
	while (arr[i])
	{
		if (*(arr[i]))
		{
			type = get_prefix_type(arr[i], file, world);
			if (!type)
				break ;
		}
		i++;
	}
	if (world->config.set != 255)
		error_throw("Missing or incorrect config lines: %s", world, 0, file);
	if (world->win_h <= 0 || world->win_w <= 0)
		error_throw("Invalid resolution", world, NULL, NULL);
	while (arr[i])
	{
		ft_arraypush_back(&(world->map->map), arr[i]);
		i++;
	}
}

static void	process_map(t_map *map, char *file, t_world *world)
{
	int		spot[2];
	char	found;

	if (!map->map)
		error_throw("Map error: %s", world, NULL, file);
	check_map(map->map, world);
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
	process_map_tex(map, world);
	process_objs(map, world);
}

void		load_map(char *file, t_world *world)
{
	int		fd;

	world->map = malloc(sizeof(t_map));
	if (!world->map)
		error_throw("Out of memory", world, NULL, NULL);
	world->map->map = NULL;
	fd = open(file, O_RDWR);
	if (fd < 0)
		error_throw("File not found: %s", world, NULL, file);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 5))
	{
		close(fd);
		error_throw("File not in .cub format: %s", world, NULL, file);
	}
	world->config.config_file = parse_file(fd, world, file);
	close(fd);
	check_cub_content(world->config.config_file, file, world);
	ft_arrayclear(&(world->config.config_file));
	process_map(world->map, file, world);
}
