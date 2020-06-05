/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstfind_plus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:08:41 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/05 14:14:37 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(const char *needle, t_list *haystack)
{
	size_t len;

	len = ft_strlen(needle);
	while (haystack)
	{
		if (ft_strncmp((char *)(haystack->content), needle, len))
			return (haystack);
		haystack = haystack->next;
	}
	return (NULL);
}
