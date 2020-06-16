/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testarr.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 10:32:13 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/16 12:20:34 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "cub3d.h"

int	main(void)
{
	char	**arr;
	int		**found;
	int		i;

	arr = ft_makearray(5, "00001", "00000", "00100", "00010", "00001");
	found = ft_arraysearch('1', arr);
	i = 0;
	while (found[i])
	{
		ft_printf("%d %d\n", (found[i])[0], (found[i])[1]);
		i++;
	}
	ft_arrayclear(&arr);
	ft_arrayclear((char ***)(&found));
	while (1) {}
	return (0);
}
