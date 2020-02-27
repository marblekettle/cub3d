/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:51:48 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:51:49 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bt;

	i = 0;
	bt = b;
	while (i < len)
	{
		bt[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
