/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 10:05:32 by bmans          #+#    #+#                */
/*   Updated: 2020/03/10 14:46:19 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"
#include <stdio.h>
#include <string.h>

void	ft_cleararray(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
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

	if (!arr || !*arr)
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

int		main(void)
{
	char	**arr;
	int		i;

	arr = ft_makearray(2, "banana");
	printf("%zu\n", ft_arraysize(arr));
	free(arr[1]);
	arr[1] = ft_strdup("cherry");
	printf("%zu\n", ft_arraysize(arr));
	i = 0;
	ft_arraypush_back(&arr, "dragonfruit");
	ft_arraypush_front(&arr, "apple");
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("%zu\n", ft_arraysize(arr));
	ft_cleararray(arr);
	printf("%zu\n", ft_arraysize(arr));
}
