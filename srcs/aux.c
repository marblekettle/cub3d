/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 12:09:51 by brendan        #+#    #+#                */
/*   Updated: 2020/03/20 12:10:30 by brendan       ########   odam.nl         */
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