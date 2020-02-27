/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:50:53 by bmans         #+#    #+#                 */
/*   Updated: 2020/01/13 15:50:54 by bmans         ########   odam.nl         */
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
		ft_putnchar_fd(print->pad, print->width - 1, 1);
	ft_putchar_fd(c, 1);
	if (print->width > 1 && print->left)
		ft_putnchar_fd(print->pad, print->width - 1, 1);
	(print->len) += print->width > 1 ? print->width : 1;
}
