/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bitmap.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:16:09 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/29 14:45:21 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
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
	ft_memcpy(data + 26, "\0\01\0\030", 4);
	ft_bzero(data + 30, 24);
}

static void	fill_data(u_int8_t *data, t_texture *image)
{
	u_int8_t	*imgdata;
	size_t		spot;
	int			pixel[2];

	imgdata = (u_int8_t *)(image->imgdata);
	pixel[1] = 0;
	while (pixel[1] < image->height)
	{
		pixel[0] = 0;
		while (pixel[0] < image->width)
		{
			spot = (size_t)(pixel[0] + (pixel[1] * image->linesize));
			imgdata = (u_int8_t *)&(image->imgdata[spot]);
			if (pixel[0] < 10)
				printf("%d %d %d, ", imgdata[0], imgdata[1], imgdata[2]);
			ft_memcpy(data, imgdata + 2, 1);
			ft_memcpy(data + 1, imgdata + 1, 1);
			ft_memcpy(data + 2, imgdata, 1);
			data += 3;
			pixel[0]++;
		}
		printf("\n");
		pixel[1]++;
	}
}

void		save_bitmap(t_texture *image, t_world *world)
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
	fd = open("./save.bmp", O_CREAT, 0666);
	printf("%d\n", fd);
	close(fd);
	fd = open("./save.bmp", O_RDWR);
	printf("%d\n", fd);
	write(fd, data, f_size);
	free(data);
	close(fd);
}
