/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 16:10:14 by bmans          #+#    #+#                */
/*   Updated: 2020/03/27 13:27:45 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static const char	g_lex[] = CONV_LIST;

static void			(*g_func[])(t_print *) = {&ft_print_char, \
	&ft_print_string, &ft_print_ptr, &ft_print_int, &ft_print_int, \
	&ft_print_uint, &ft_print_uint, &ft_print_uint, &ft_print_char};

static void			formatprint(t_print *print)
{
	print->width = 0;
	print->prec = -1;
	print->pad = ' ';
	print->left = 0;
	print->conv = 0;
	(print->form)++;
	ft_print_flags(print);
	if (print->conv)
	{
		g_func[ft_strchr(g_lex, (int)print->conv) - g_lex](print);
		if (print->form)
			(print->form)++;
	}
}

static void			normalprint(t_print *print)
{
	char	*end;

	end = ft_strchr(print->form, '%');
	if (!end)
		end = ft_strchr(print->form, '\0');
	while (*(print->form) && print->form < end)
	{
		ft_putchar_fd(*(print->form), print->out);
		(print->len)++;
		(print->form)++;
	}
}

int					ft_printf(const char *format, ...)
{
	t_print	print;

	va_start(print.ap, format);
	print.out = 1;
	print.form = (char *)format;
	print.len = 0;
	while (*(print.form))
	{
		if (*(print.form) == '%')
			formatprint(&print);
		else
			normalprint(&print);
		if (print.form == NULL)
			return (-1);
	}
	va_end(print.ap);
	return (print.len);
}

int					ft_printf_fd(int fd, const char *format, ...)
{
	t_print	print;

	va_start(print.ap, format);
	print.out = fd;
	print.form = (char *)format;
	print.len = 0;
	while (*(print.form))
	{
		if (*(print.form) == '%')
			formatprint(&print);
		else
			normalprint(&print);
		if (print.form == NULL)
			return (-1);
	}
	va_end(print.ap);
	return (print.len);	
}