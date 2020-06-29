/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 10:03:54 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/29 10:04:33 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	check_spot(char **map, int i, int j)
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
}
