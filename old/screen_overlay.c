/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screen_overlay.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 10:56:13 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/24 14:28:43 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	screen_overlay(t_texture *bot_screen, t_texture *top_screen)
{
	int		pixel[2];
	long	spot;

	ft_bzero(pixel, 8);
	spot = 0;
	while (pixel[1] < bot_screen->height)
	{
		pixel[0] = 0;
		while (pixel[0] < bot_screen->width)
		{
			spot = pixel[0] + (pixel[1] * bot_screen->linesize);
			if (top_screen->imgdata[spot] != 0x02000000)
				bot_screen->imgdata[spot] = top_screen->imgdata[spot];
			pixel[0]++;
		}
		pixel[1]++;
	}
}

