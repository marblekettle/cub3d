/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:03:53 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/17 14:04:36 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	swap_int(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		abs_int(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

double	sign(double num)
{
	return (num >= 0.0 ? 1.0 : -1.0);
}
