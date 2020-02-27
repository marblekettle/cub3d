/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:52:51 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:52:51 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	joined = malloc(sizeof(char) * (len + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		joined[i] = *(s1 + i);
		i++;
	}
	i = 0;
	while (*(s2 + i))
	{
		joined[i + len] = *(s2 + i);
		i++;
	}
	joined[len + i] = 0;
	return (joined);
}
