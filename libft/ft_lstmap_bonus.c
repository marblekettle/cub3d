/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:50:25 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:50:25 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*map;
	t_list			*first;

	if (!lst)
		return (NULL);
	first = ft_lstnew(f(lst->content));
	if (!first)
		return (NULL);
	map = first;
	while (lst->next)
	{
		lst = lst->next;
		ft_lstadd_back(&map, ft_lstnew(f(lst->content)));
		if (!map)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		map = map->next;
	}
	return (first);
}
