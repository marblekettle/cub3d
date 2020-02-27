/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 09:48:25 by bmans         #+#    #+#                 */
/*   Updated: 2019/10/30 09:51:24 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	i = 0;
	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	while (i < size * count)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
