/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 14:55:31 by bmans         #+#    #+#                 */
/*   Updated: 2019/12/06 14:55:32 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static U_INT	ft_digitcount_base(U_INT n, U_INT base)
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

char			*ft_itoa_base(U_INT n, U_INT base, char *basedigits)
{
	char	*a;
	U_INT	digits;

	if (base < 2 || ft_strlen(basedigits) != base)
		return (ft_strdup(""));
	digits = ft_digitcount_base(n, base);
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
