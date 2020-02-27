/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:51:09 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:51:09 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*st;

	i = 0;
	st = (unsigned char*)s;
	while (i < n)
	{
		if (st[i] == (unsigned char)c)
			return ((void*)(st + i));
		i++;
	}
	return (NULL);
}
