/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_string.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:50:59 by bmans          #+#    #+#                */
/*   Updated: 2020/03/27 13:28:49 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_string(t_print *print)
{
	char	*tstr;
	char	*str;

	tstr = va_arg(print->ap, char*);
	if (!tstr)
		tstr = "(null)";
	if ((int)ft_strlen(tstr) < print->prec || print->prec == -1)
		print->prec = (int)ft_strlen(tstr);
	str = malloc(sizeof(char) * (print->prec + 1));
	if (str)
	{
		ft_strlcpy(str, tstr, print->prec + 1);
		if (print->width > (int)ft_strlen(str))
			str = ft_print_resize(str, print);
	}
	if (!str)
	{
		print->form = NULL;
		return ;
	}
	ft_putstr_fd(str, print->out);
	print->len += ft_strlen(str);
	free(str);
}
