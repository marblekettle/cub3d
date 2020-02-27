/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:52:45 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:52:45 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (copy)
	{
		while (*(s1 + i))
		{
			copy[i] = *(s1 + i);
			i++;
		}
		copy[i] = '\0';
	}
	return (copy);
}
