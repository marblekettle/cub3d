/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:53:43 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:53:44 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char*)haystack);
	i = 0;
	while (*(haystack + i) && i < len)
	{
		if (*needle == *(haystack + i))
		{
			j = 0;
			while ((*(haystack + i + j) == *(needle + j)) && (i + j < len))
			{
				j++;
				if (!(*(needle + j)))
					return ((char*)(haystack + i));
			}
		}
		i++;
	}
	return (NULL);
}
