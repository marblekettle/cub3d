/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bitmap.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:16:09 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/01 17:37:21 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static void	make_header(int fd, t_texture *image)
{
	u_int32_t	f_size;
	u_int32_t	dim;

	f_size = (u_int32_t)(3 * image->height * image->width) + 54;
	write(fd, "BM", 2);
	write(fd, (u_int8_t *)(&f_size), 4);
	write(fd, "\0\0\0\0\066\0\0\0\050\0\0\0", 12);
	dim = (u_int32_t)(image->width);
	write(fd, (u_int8_t *)(&dim), 4);
	dim = (u_int32_t)(image->height);
	write(fd, (u_int8_t *)(&dim), 4);
	write(fd, "\01\0\030\0", 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 24);
}

static void	fill_pad(int fd, char pad)
{
	while (pad)
	{
		write(fd, "\0", 1);
		pad--;
	}
}

static void	fill_data(int fd, t_texture *image)
{
	u_int8_t	*imgdata;
	size_t		spot;
	int			pixel[2];

	imgdata = (u_int8_t *)(image->imgdata);
	pixel[1] = image->height;
	while (pixel[1] >= 0)
	{
		pixel[1]--;
		pixel[0] = 0;
		while (pixel[0] < image->width)
		{
			spot = (size_t)(pixel[0] + (pixel[1] * image->linesize));
			imgdata = (u_int8_t *)&(image->imgdata[spot]);
			write(fd, imgdata, 3);
			pixel[0]++;
		}
		if ((image->width * 3) % 4)
			fill_pad(fd, 4 - ((image->width * 3) % 4));
	}
}

void		save_bitmap(t_texture *image, t_world *world, char *name)
{
	int			fd;

	fd = open(name, O_CREAT | O_RDWR, 0666);
	if (fd < -1)
		error_throw("Could not create file: %s", world, NULL, name);
	make_header(fd, image);
	fill_data(fd, image);
	close(fd);
}
