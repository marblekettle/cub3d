/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 15:53:36 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 15:53:37 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (*(s1 + i) && *(s2 + i) && (*(s1 + i) == *(s2 + i)) && i < n)
		i++;
	return (*(unsigned char*)(s1 + i) - *(unsigned char*)(s2 + i));
}
