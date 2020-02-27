/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:16:35 by bmans         #+#    #+#                 */
/*   Updated: 2019/10/28 15:16:39 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			ft_iswhite_static(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
			|| c == ' ' || c == 133 || c == 160);
}

int					ft_atoi(const char *str)
{
	unsigned long	num;
	char			neg;

	num = 0;
	neg = 1;
	while (ft_iswhite_static(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		neg = (*str == '-') ? -1 : 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		str++;
		if (num > LONG_MAX)
			return ((neg == -1 && num - 1 == LONG_MAX) ? 0 : -1);
	}
	return (neg * (int)num);
}
