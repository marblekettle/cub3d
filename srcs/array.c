/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 10:05:32 by bmans          #+#    #+#                */
/*   Updated: 2020/03/20 16:58:39 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

void	ft_arrayclear(char ***arr)
{
	int i;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
	(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

size_t	ft_arraysize(char **arr)
{
	size_t len;

	len = 0;
	if (arr)
	{
		while (arr[len])
			len++;
	}
	return (len);
}

void	ft_arraypush_back(char ***arr, char *new)
{
	char	**newarr;
	size_t	len;

	if (!arr)
		return ;
	len = ft_arraysize(*arr);
	newarr = malloc(sizeof(char *) * (len + 2));
	if (!newarr)
		return ;
	newarr[len + 1] = NULL;
	newarr[len] = ft_strdup(new);
	while (len > 0)
	{
		len--;
		newarr[len] = (*arr)[len];
	}
	free(*arr);
	*arr = newarr;
}

void	ft_arraypush_front(char ***arr, char *new)
{
	char	**newarr;
	size_t	len;

	if (!arr || !*arr)
		return ;
	len = ft_arraysize(*arr);
	newarr = malloc(sizeof(char *) * (len + 2));
	if (!newarr)
		return ;
	newarr[len + 1] = NULL;
	newarr[0] = ft_strdup(new);
	while (len > 0)
	{
		newarr[len] = (*arr)[len - 1];
		len--;
	}
	free(*arr);
	*arr = newarr;
}

char	**ft_makearray(size_t len, ...)
{
	va_list args;
	size_t	i;
	char	*str;
	char	**arr;

	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	va_start(args, len);
	i = 0;
	while (i < len)
	{
		str = va_arg(args, char *);
		arr[i] = ft_strdup(str);
		i++;
	}
	va_end(args);
	arr[i] = NULL;
	return (arr);
}
