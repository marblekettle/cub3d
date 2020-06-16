/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrayaux.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 16:05:23 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/16 12:19:00 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

char	ft_arrayfind(int *spot, char *term, char **arr)
{
	int		i;
	char	*found;

	found = NULL;
	while (*term)
	{
		i = 0;
		while (arr[i])
		{
			found = ft_strchr(arr[i], *term);
			if (found)
			{
				spot[0] = found - arr[i];
				spot[1] = i;
				return (*term);
			}
			i++;
		}
		term++;
	}
	return (0);
}

void	ft_arraypushbytes(char ***arr, void *new, size_t bytes)
{
	char	**newarr;
	char	*new_bytes;
	size_t	len;

	len = ft_arraysize(*arr);
	newarr = malloc(sizeof(char *) * (len + 2));
	if (!newarr)
		return ;
	new_bytes = malloc(bytes);
	if (!new_bytes)
	{
		free(newarr);
		return ;
	}
	ft_memcpy(new_bytes, new, bytes);
	newarr[len + 1] = NULL;
	newarr[len] = new_bytes;
	while (len > 0)
	{
		len--;
		newarr[len] = (*arr)[len];
	}
	free(*arr);
	*arr = newarr;
}

int		**ft_arraysearch(char term, char **arr)
{
	int		**spotarr;
	int		spot[2];
	char	*found;

	spotarr = (int **)ft_makearray(0);
	ft_bzero(spot, 8);
	while (arr[spot[1]])
	{
		spot[0] = 0;
		while (1)
		{
			found = ft_strchr(arr[spot[1]] + spot[0], term);
			if (!found)
				break ;
			else
			{
				spot[0] = found - arr[spot[1]];
				ft_arraypushbytes((char ***)(&spotarr), spot, 8);
				spot[0]++;
			}
		}
		spot[1]++;
	}
	return (spotarr);
}
