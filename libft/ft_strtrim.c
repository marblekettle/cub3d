/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:54:00 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:54:01 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_isin(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	first;
	unsigned int	last;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (first < last && ft_isin(s1[first], set))
		first++;
	while (last > 0 && ft_isin(s1[last - 1], set))
		last--;
	if (last < first)
		last = first;
	return (ft_substr(s1, first, last - first));
}
