/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:51:37 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:51:38 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if (dst != src)
	{
		if (dst > src && dst < src + len)
		{
			i = len;
			while (i > 0)
			{
				i--;
				((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			}
		}
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
