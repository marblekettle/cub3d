/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base_prec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:36:04 by bmans         #+#    #+#                 */
/*   Updated: 2020/01/13 15:36:05 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static U_INT	ft_digitcount_base(U_LL n, U_INT base)
{
	unsigned int digits;

	digits = 1;
	while (n > base - 1)
	{
		n = n / base;
		digits++;
	}
	return (digits);
}

char			*ft_itoa_base_prec(U_LL n, char *basedigits, int prec)
{
	char	*a;
	U_INT	digits;
	U_INT	base;

	base = ft_strlen(basedigits);
	if (base < 2 || (prec == 0 && n == 0))
		return (ft_strdup(""));
	digits = ft_digitcount_base(n, base);
	if (digits < (U_INT)prec && prec != -1)
		digits = prec;
	a = malloc(sizeof(char) * (digits + 1));
	if (a)
	{
		a[digits] = '\0';
		while (digits > 0)
		{
			digits--;
			a[digits] = basedigits[(U_INT)(n % base)];
			n = (n / base);
		}
	}
	return (a);
}
