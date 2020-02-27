/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint_plus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 11:06:08 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/13 11:06:08 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	unsigned int	l;
	int				strl;

	l = 0;
	while (lst)
	{
		strl = (int)ft_strlen(lst->content);
		ft_putstr_fd("o-", 1);
		ft_putnchar_fd('-', ft_max(strl, 5), 1);
		ft_putstr_fd("-o\n| #", 1);
		ft_putchar_fd('0' + l, 1);
		ft_putnchar_fd(' ', ft_max(strl - 2, 3), 1);
		ft_putstr_fd(" |\n| ", 1);
		ft_putstr_fd(lst->content, 1);
		ft_putnchar_fd(' ', ft_max(-strl + 5, 0), 1);
		ft_putstr_fd(" |\no-", 1);
		ft_putnchar_fd('-', ft_max(strl, 5), 1);
		ft_putstr_fd("-o\n", 1);
		if (lst->next)
			ft_putstr_fd("  |\n  v\n", 1);
		lst = lst->next;
		l++;
	}
}
