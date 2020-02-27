/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:54:07 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:54:07 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	subs = malloc(sizeof(char) * (len + 1));
	if (subs)
	{
		i = 0;
		while (i < (unsigned int)len && start + i < ft_strlen(s))
		{
			subs[i] = *(s + start + i);
			i++;
		}
		subs[i] = 0;
	}
	return (subs);
}
