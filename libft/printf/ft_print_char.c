/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:50:53 by bmans          #+#    #+#                */
/*   Updated: 2020/03/27 13:29:00 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_char(t_print *print)
{
	int c;

	if (print->conv == '%')
		c = '%';
	else
		c = va_arg(print->ap, int);
	if (print->width > 1 && !print->left)
		ft_putnchar_fd(print->pad, print->width - 1, print->out);
	ft_putchar_fd(c, print->out);
	if (print->width > 1 && print->left)
		ft_putnchar_fd(print->pad, print->width - 1, print->out);
	(print->len) += print->width > 1 ? print->width : 1;
}
