/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_int.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:51:12 by bmans          #+#    #+#                */
/*   Updated: 2020/03/27 13:28:35 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_int(t_print *print)
{
	int		num;
	char	*nstr;

	num = va_arg(print->ap, int);
	nstr = ft_itoa_prec(num, print->prec);
	if (nstr && print->width > (int)ft_strlen(nstr))
		nstr = ft_print_resize(nstr, print);
	if (!nstr)
	{
		print->form = NULL;
		return ;
	}
	ft_putstr_fd(nstr, print->out);
	print->len += ft_strlen(nstr);
	free(nstr);
}
