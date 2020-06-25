/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_uint.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:51:18 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/25 13:58:22 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_uint(t_print *print)
{
	u_int32_t	num;
	char		*nstr;
	char		*basestr;

	basestr = "0123456789";
	if (print->conv == 'x')
		basestr = "0123456789abcdef";
	else if (print->conv == 'X')
		basestr = "0123456789ABCDEF";
	num = va_arg(print->ap, u_int32_t);
	nstr = ft_itoa_base_prec(num, basestr, print->prec);
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
