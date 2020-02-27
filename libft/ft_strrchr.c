/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:53:53 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:53:53 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*found;

	i = 0;
	found = NULL;
	while (*(s + i))
	{
		if (*(s + i) == c)
			found = (char*)s + i;
		i++;
	}
	if (!c)
		found = (char*)s + i;
	return (found);
}
