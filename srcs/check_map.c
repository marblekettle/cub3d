/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 10:03:54 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/03 15:26:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"

/* static char	check_spot(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[j + 1])
		return (0);
	if (!map[j][i + 1] || map[j][i + 1] == ' ')
		return (0);
	if (!map[j][i - 1] || map[j][i - 1] == ' ')
		return (0);
	if ((int)ft_strlen(map[j - 1]) <= i || (int)ft_strlen(map[j + 1]) <= i)
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

char		check_map(char **map)
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
}*/

static char	get_spot(int x, int y, char **arr)
{
	if (y < 0 || y >= (int)ft_arraysize(arr))
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(arr[y]))
		return (' ');
	return (arr[y][x]);
}

static char	floodfill(int x, int y, char **arr)
{
	int result;

	if (get_spot(x, y, arr) == ' ')
		return (1);
	if (get_spot(x, y, arr) == '1')
		return (0);
	else
	{
		result = 0;
		arr[y][x] = '1';
		result += floodfill(x - 1, y - 1, arr);
		result += floodfill(x - 1, y, arr);
		result += floodfill(x - 1, y + 1, arr);
		result += floodfill(x, y - 1, arr);
		result += floodfill(x, y + 1, arr);
		result += floodfill(x + 1, y - 1, arr);
		result += floodfill(x + 1, y, arr);
		result += floodfill(x + 1, y + 1, arr);
		return (result > 0 ? 1 : 0);
	}
}

static char	unique_player_start(char **map)
{
	int		spot[2];
	char	found;

	found = 0;
	spot[1] = 0;
	while (map[spot[1]])
	{
		spot[0] = 0;
		while (map[spot[1]][spot[0]])
		{
			if (ft_strchr("NSWE", map[spot[1]][spot[0]]))
			{
				if (found)
					return (0);
				else
					found = 1;
			}
			spot[0]++;
		}
		spot[1]++;
	}
	return (1);
}

static char	map_valid(char **map)
{
	int	spot[2];

	spot[1] = 0;
	while (map[spot[1]])
	{
		spot[0] = 0;
		while (map[spot[1]][spot[0]])
		{
			if (!ft_strchr("012NSWE ", map[spot[1]][spot[0]]))
				return (0);
			spot[0]++;
		}
		spot[1]++;
	}
	return (1);
}

void		check_map(char **map, t_world *world)
{
	int		spot[2];
	int		index;
	char	**newarr;
	char	open;

	if (!map_valid(map))
		error_throw("Invalid map element", world, NULL, NULL);
	if (!unique_player_start(map))
		error_throw("Multiple player start", world, NULL, NULL);
	ft_arrayfind(spot, "NSWE", map);
	index = 0;
	newarr = NULL;
	while (map[index])
	{
		ft_arraypush_back(&newarr, map[index]);
		index++;
	}
	open = floodfill(spot[0], spot[1], newarr);
	ft_arrayclear(&newarr);
	if (open)
		error_throw("Invalid map layout", world, NULL, NULL);
}
