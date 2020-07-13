/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 10:20:05 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/10 14:56:39 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
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

void		set_resolution(char *line, t_world *world)
{
	char	**split;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i]) || line[i] == ' '))
			error_throw("Incorrect resolution config", world, NULL, NULL);
		i++;
	}
	split = ft_split(line, ' ');
	if (!(ft_arraysize(split) == 2))
	{
		ft_arrayclear(&split);
		error_throw("Incorrect resolution config", world, NULL, NULL);
	}
	world->win_w = ft_atoi(split[0]);
	world->win_h = ft_atoi(split[1]);
	ft_arrayclear(&split);
}

char		number_sanity(char **arr)
{
	int		i;
	char	**split;
	int		count;

	i = 0;
	while (i < 3)
	{
		split = ft_split(arr[i], ' ');
		if (!split)
			return (0);
		count = ft_arraysize(split);
		ft_arrayclear(&split);
		if (count > 1)
			return (0);
		i++;
	}
	return (1);
}

char		**color_sanity(char *line, t_world *world)
{
	char	**split;
	size_t	i;
	char	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i]) || line[i] == ' ' || line[i] == ','))
			error_throw("Incorrect color config", world, NULL, NULL);
		if (line[i] == ',')
			comma++;
		i++;
	}
	split = ft_split(line, ',');
	if (ft_arraysize(split) != 3 || comma > 2 || !number_sanity(split))
	{
		ft_arrayclear(&split);
		error_throw("Incorrect color config", world, NULL, NULL);
	}
	return (split);
}

void		set_flcl_color(char *line, char fl_cl, t_world *world)
{
	char		**split;
	u_int32_t	color[4];
	u_int8_t	c_byte[3];

	split = color_sanity(line, world);
	color[0] = (u_int32_t)ft_atoi(split[0]);
	color[1] = (u_int32_t)ft_atoi(split[1]);
	color[2] = (u_int32_t)ft_atoi(split[2]);
	ft_arrayclear(&split);
	c_byte[0] = (u_int8_t)color[0];
	c_byte[1] = (u_int8_t)color[1];
	c_byte[2] = (u_int8_t)color[2];
	if (color[0] > c_byte[0] || color[1] > c_byte[1] || color[2] > c_byte[2])
		error_throw("Incorrect color config", world, NULL, NULL);
	color[3] = (c_byte[2] + (c_byte[1] << 8) + (c_byte[0] << 16));
	if (fl_cl)
		world->map->cl_color = color[3];
	else
		world->map->fl_color = color[3];
}

void		config_action(char index, char *line, t_world *world)
{
	while (*line == ' ')
		line++;
	if (index == 0)
		world->config.path_no = ft_strdup(line);
	else if (index == 1)
		world->config.path_ea = ft_strdup(line);
	else if (index == 2)
		world->config.path_so = ft_strdup(line);
	else if (index == 3)
		world->config.path_we = ft_strdup(line);
	else if (index == 4)
		world->config.path_s = ft_strdup(line);
	else if (index == 5)
		set_resolution(line, world);
	else if (index == 6)
		set_flcl_color(line, 0, world);
	else if (index == 7)
		set_flcl_color(line, 1, world);
}

char		get_prefix_type(char *line, char *file, t_world *world)
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

void		check_cub_content(char **arr, char *file, t_world *world)
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

static void		process_sprite(const char *file, t_world *world)
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

static void		process_map_tex(t_map *map, t_world *world)
{
	map->no_tex = load_texture(world, world->config.path_no);
	map->ea_tex = load_texture(world, world->config.path_ea);
	map->so_tex = load_texture(world, world->config.path_so);
	map->we_tex = load_texture(world, world->config.path_we);
	process_sprite(world->config.path_s, world);
}

static void		process_map(t_map *map, char *file, t_world *world)
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

/*int			main(void)
{
	t_world world;

	ft_bzero(&world, sizeof(t_world));
	load_map("./test.cub", &world);
	ft_printf("Valid map!\n");
	return (0);
}*/

/*
**	check invalid res (0 >=) (done)
**	check for invalid chars (done)
**	reintroduce map array checks (done)
**	image file errors (done)
**	valid map character set (done)
**	wall element that is not 0 or 1 (done)
** 
*/
