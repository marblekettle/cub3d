/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ptr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:51:07 by bmans          #+#    #+#                */
/*   Updated: 2020/03/27 13:28:40 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_ptr(t_print *print)
{
	U_LL	ptr;
	char	*tpstr;
	char	*pstr;

	ptr = va_arg(print->ap, U_LL);
	pstr = NULL;
	tpstr = ft_itoa_base_prec(ptr, "0123456789abcdef", print->prec);
	if (tpstr)
	{
		pstr = ft_strjoin("0x", tpstr);
		free(tpstr);
	}
	if (pstr && print->width > (int)ft_strlen(pstr))
		pstr = ft_print_resize(pstr, print);
	if (!pstr)
	{
		print->form = NULL;
		return ;
	}
	ft_putstr_fd(pstr, print->out);
	print->len += ft_strlen(pstr);
	free(pstr);
}
