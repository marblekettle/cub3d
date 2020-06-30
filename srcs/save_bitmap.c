/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bitmap.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:16:09 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/30 16:40:53 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static void	make_header(u_int8_t *data, t_texture *image)
{
	u_int32_t	f_size;
	u_int32_t	offset;

	f_size = (u_int32_t)(3 * image->height * image->width) + 54;
	ft_memcpy(data, "BM", 2);
	ft_memcpy(data + 2, &f_size, 4);
	ft_bzero(data + 6, 4);
	offset = 54;
	ft_memcpy(data + 10, &offset, 4);
	offset = 40;
	ft_memcpy(data + 14, &offset, 4);
	offset = (u_int32_t)(image->width);
	ft_memcpy(data + 18, &offset, 4);
	offset = (u_int32_t)(image->height);
	ft_memcpy(data + 22, &offset, 4);
	ft_memcpy(data + 26, "\01\0\030\0", 4);
	ft_bzero(data + 30, 24);
}

static void	fill_data(u_int8_t *data, t_texture *image)
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
			ft_memcpy(data, imgdata, 1);
			ft_memcpy(data + 1, imgdata + 1, 1);
			ft_memcpy(data + 2, imgdata + 2, 1);
			data += 3;
			pixel[0]++;
		}
	}
}

void		save_bitmap(t_texture *image, t_world *world, char *name)
{
	int			fd;
	size_t		f_size;
	u_int8_t	*data;

	f_size = (size_t)((3 * image->height * image->width) + 54);
	data = malloc(sizeof(u_int8_t) * f_size);
	if (!data)
		error_throw("Out of memory", world, NULL, NULL);
	make_header(data, image);
	fill_data(data + 54, image);
	fd = open(name, O_CREAT | O_RDWR, 0666);
	if (fd < -1)
		error_throw("Could not create file: %s", world, data, name);
	write(fd, data, f_size);
	free(data);
	close(fd);
}
