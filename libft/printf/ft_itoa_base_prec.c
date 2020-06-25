/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base_prec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:36:04 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/25 14:00:08 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static u_int32_t	ft_digitcount_base(u_int64_t n, u_int32_t base)
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

char				*ft_itoa_base_prec(u_int64_t n, char *basedigits, int prec)
{
	char		*a;
	u_int32_t	digits;
	u_int32_t	base;

	base = ft_strlen(basedigits);
	if (base < 2 || (prec == 0 && n == 0))
		return (ft_strdup(""));
	digits = ft_digitcount_base(n, base);
	if (digits < (u_int32_t)prec && prec != -1)
		digits = prec;
	a = malloc(sizeof(char) * (digits + 1));
	if (a)
	{
		a[digits] = '\0';
		while (digits > 0)
		{
			digits--;
			a[digits] = basedigits[(u_int32_t)(n % base)];
			n = (n / base);
		}
	}
	return (a);
}
