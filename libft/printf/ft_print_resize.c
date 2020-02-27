/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_resize.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:40:54 by bmans         #+#    #+#                 */
/*   Updated: 2020/01/13 15:40:55 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	fix_exceptions(char *str, t_print *print)
{
	if ((print->conv == 'd' || print->conv == 'i') && \
		print->pad == '0' && ft_strchr(str, '-'))
	{
		*(ft_strchr(str, '-')) = '0';
		str[0] = '-';
	}
	if (print->conv == 'p' && print->pad == '0')
	{
		*(ft_strchr(str, 'x')) = '0';
		str[1] = 'x';
	}
}

char		*ft_print_resize(char *str, t_print *print)
{
	U_INT	size;
	char	*newstr;

	newstr = malloc(sizeof(char) * (print->width + 1));
	if (newstr)
	{
		newstr[print->width] = '\0';
		size = ft_strlen(str);
		ft_memset(newstr, (int)print->pad, print->width);
		if (print->left)
			ft_memcpy(newstr, str, size);
		else
			ft_memcpy(newstr + print->width - size, str, size);
		fix_exceptions(newstr, print);
	}
	free(str);
	return (newstr);
}
