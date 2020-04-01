/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 15:39:17 by brendan        #+#    #+#                */
/*   Updated: 2020/04/01 15:00:35 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

#include <stdio.h>

static double	jump_val(double num, char align, char vert)
{
	if (align > 0)
	{
		if (vert)
			return (1.0);
		else
			return (ceil(num) - num);
	}
	else if (align < 0)
	{
		if (vert)
			return (-1.0);
		else
			return (floor(num) - num);
	}
	else
		return (0.0);
}

static double	jump_point(double *pos, double *dir, char *vert)
{
	double	delta[2];

	delta[0] = jump_val(pos[0], sign(dir[0]), *vert & 1) / dir[0];
	delta[1] = jump_val(pos[1], sign(dir[1]), *vert & 2) / dir[1];
	*vert = fabs(delta[1]) < fabs(delta[0]) ? 2 : 1;
	pos[0] += delta[*vert - 1] * dir[0];
	pos[1] += delta[*vert - 1] * dir[1];
	return (delta[*vert - 1]);
}

static char		check_mappoint(int *point, t_map *map)
{
	if (point[0] < 0 || point[1] < 0)
		return (' ');
	if (point[1] >= ft_arraysize(map->map))
		return (' ');
	if (point[0] >= ft_strlen(map->map[point[1]]))
		return (' ');
	return (map->map[point[1]][point[0]]);
}

void			cast_ray(double *pos_dir, t_ray *ray, t_world *world)
{
	char	vert;

	ft_memcpy(ray->point, pos_dir, 16);
	ray->map_point[0] = (int)floor(pos_dir[0]);
	ray->map_point[1] = (int)floor(pos_dir[1]);
	vert = 0;
	ray->dist = 0;
	ray->content = check_mappoint(ray->map_point, world->map);
	while (ray->content != ' ' && ray->content != '1' && ray->dist < MAX_DIST)
	{
		ray->dist += jump_point(ray->point, pos_dir + 2, &vert);
		if (vert == 2)
			ray->map_point[1] += (pos_dir[3] > 0.0) ? 1 : -1;
		else if (vert == 1)
			ray->map_point[0] += (pos_dir[2] > 0.0) ? 1 : -1;
		ray->content = check_mappoint(ray->map_point, world->map);
	}
	if (vert == 1)
		ray->side = (ray->point[0] - 0.5 < ray->map_point[0]) ? 'W' : 'E';
	else if (vert == 2)
		ray->side = (ray->point[1] - 0.5 < ray->map_point[1]) ? 'N' : 'S';
}