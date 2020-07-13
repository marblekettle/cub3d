/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_parse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 10:00:36 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/13 10:07:34 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	set_resolution(char *line, t_world *world)
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

static char	number_sanity(char **arr)
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

static char	**color_sanity(char *line, t_world *world)
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

static void	set_flcl_color(char *line, char fl_cl, t_world *world)
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
