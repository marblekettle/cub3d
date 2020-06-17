/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec2.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:07:19 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/17 14:07:29 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

void	vec2_join(int *vecout, int *vec1, int *vec2)
{
	int	newvec[4];

	ft_memcpy(newvec, vec1, 8);
	ft_memcpy(newvec + 2, vec2, 8);
	ft_memcpy(vecout, newvec, 16);
}

void	vec2_rot(double *out, double *in, double r, double theta)
{
	double	tvec[2];

	tvec[0] = in[0] * r * cos(theta) - in[1] * r * sin(theta);
	tvec[1] = in[0] * r * sin(theta) + in[1] * r * cos(theta);
	ft_memcpy(out, tvec, 16);
}
