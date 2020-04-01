/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arrayaux.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 16:05:23 by brendan        #+#    #+#                */
/*   Updated: 2020/03/31 16:48:47 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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