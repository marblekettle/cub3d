/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:51:20 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:51:20 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (*((unsigned char*)s1 + i) == *((unsigned char*)s2 + i))
	{
		if (i < n - 1)
			i++;
		else
			break ;
	}
	return (*((unsigned char*)s1 + i) - *((unsigned char*)s2 + i));
}
