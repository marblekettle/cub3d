/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 12:09:51 by brendan        #+#    #+#                */
/*   Updated: 2020/03/24 16:31:41 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	swap_int(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	    abs_int(int num)
	{
		if (num < 0)
			return (-num);
		return (num);
	}

double	sign(double num)
{
	return (num >= 0.0 ? 1.0 : -1.0);
}