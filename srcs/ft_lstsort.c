/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 12:32:23 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/24 10:20:09 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	lstswap(t_list *list1, t_list *list2)
{
	void	*temp;

	temp = list1->content;
	list1->content = list2->content;
	list2->content = temp;
}

static void	lstsortiter(t_list *list, double (*crit)(t_list *))
{
	if (list->next->next)
		lstsortiter(list->next, crit);
	if (crit(list) > crit(list->next))
		lstswap(list, list->next);
}

void		ft_lstsort(t_list *list, double (*crit)(t_list *))
{
	t_list *startlist;

	startlist = list;
	while (startlist->next)
	{
		lstsortiter(startlist, crit);
		startlist = startlist->next;
	}
}
