/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 13:34:49 by bmans          #+#    #+#                */
/*   Updated: 2020/03/12 14:44:35 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>

char	file_exists(char *file)
{
	int fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
		return (0);
	else
		close(fd);
	return (1);
}

int		get_texture_pixel(t_texture *texture, int x, int y)
{
	if (x >= texture->width || y >= texture->height)
		return (0);
	else
		return ((texture->imgdata)[x + texture->linesize * y]);
}

void	*open_texture(t_world *world, char *file, t_texture *texture)
{
	void		*img;
	int			width;
	int			height;

	img = NULL;
	if (!file_exists(file))
	{
		perror("Error: Image file not found\n");
		return (0);
	}
	if (ft_strncmp(".png", file + ft_strlen(file) - 4, 4) == 0)
		img = mlx_png_file_to_image(world->mlx, file, &width, &height);
	else if (ft_strncmp(".xpm", file + ft_strlen(file) - 4, 4) == 0)
		img = mlx_xpm_file_to_image(world->mlx, file, &width, &height);
	else
	{
		perror("Error: Image file is not of format .png or .xpm\n");
		return (0);
	}
	if (!img)
		perror("Error: Loading image failed\n");
	texture->width = width;
	texture->height = height;
	return (img);
}

t_texture	*load_texture(t_world *world, char *file)
{
	t_texture	*tex;
	void		*img;
	char		*imgdata;
	int			linesize;
	int			bits_pp;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		error_throw("Error: Out of memory\n", world, NULL);
	img = open_texture(world, file, tex);
	imgdata = mlx_get_data_addr(img, &bits_pp, &linesize, &(tex->endian));
	tex->imgdata = (uint32_t *)imgdata;
	tex->bytes_pp = bits_pp / 8;
	tex->linesize = linesize / tex->bytes_pp;
	ft_lstadd_back(&(world->l_textures), ft_lstnew(tex));
	return(tex);
}

void		clear_texture(void *texture)
{
	t_texture *texture_ptr;

	texture_ptr = (t_texture *)texture;
	if (texture_ptr)
		free(texture_ptr);
}
