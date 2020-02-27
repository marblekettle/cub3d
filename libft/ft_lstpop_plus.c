/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstpop_plus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 11:05:47 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/13 11:05:48 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **lst)
{
	t_list *temp;

	if (!lst && !*lst)
		return (NULL);
	temp = *lst;
	(*lst) = (*lst)->next;
	temp->next = NULL;
	return (temp);
}
