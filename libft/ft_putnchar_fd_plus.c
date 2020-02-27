/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnchar_fd_plus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 11:09:04 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/13 11:09:04 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar_fd(int c, size_t n, int fd)
{
	while (n > 0)
	{
		ft_putchar_fd(c, fd);
		n--;
	}
}
