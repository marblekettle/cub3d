/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:49:12 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:49:13 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_digitcount(int n)
{
	unsigned int digits;

	digits = 1;
	if (n < 0)
		digits++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char				*ft_itoa(int n)
{
	char			*a;
	unsigned int	digits;
	char			neg;

	neg = (n < 0) ? 1 : 0;
	digits = ft_digitcount(n);
	a = malloc(sizeof(char) * (digits + 1));
	if (a)
	{
		a[digits] = 0;
		while (digits > 0)
		{
			digits--;
			a[digits] = ((n > 0) ? (n % 10) : -(n % 10)) + '0';
			n = (n > 0) ? (n / 10) : -(n / 10);
		}
		if (neg)
			a[0] = '-';
	}
	return (a);
}
