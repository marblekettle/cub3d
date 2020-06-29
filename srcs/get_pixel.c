/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 09:56:59 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/29 09:57:29 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	*get_pixel(t_texture *tex, int *pixel)
{
	if (pixel[0] < tex->width && pixel[1] < tex->height)
		return (&(tex->imgdata[pixel[0] + (tex->linesize * pixel[1])]));
	else
		return (NULL);
}

u_int32_t	*get_pixel_scaled(t_texture *tex, double *point)
{
	int	pixel[2];

	pixel[0] = (int)(point[0] * tex->width);
	pixel[1] = (int)(point[1] * tex->height);
	if (pixel[0] >= tex->width)
		pixel[0] = tex->width - 1;
	if (pixel[1] >= tex->height)
		pixel[1] = tex->height - 1;
	return (get_pixel(tex, pixel));
}
