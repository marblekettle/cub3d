/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:51:01 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:51:02 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*d;
	char	*s;
	char	ch;

	ch = (unsigned char)c;
	s = (char*)src;
	d = (char*)dst;
	while (n)
	{
		*d = *s;
		d++;
		if (*s == ch)
			return (d);
		s++;
		n--;
	}
	return (NULL);
}
