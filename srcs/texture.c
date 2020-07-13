/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/26 21:44:35 by brendan       #+#    #+#                 */
/*   Updated: 2020/07/10 14:22:00 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>

static void	*open_texture(t_world *world, char *file, t_texture *texture)
{
	void	*img;
	int		width;
	int		height;
	int		fd;

	img = NULL;
	width = 0;
	height = 0;
	fd = open(file, O_RDWR);
	if (fd < 0)
		error_throw("File not found: %s", world, NULL, file);
	close(fd);
	if (ft_strncmp(".xpm", file + ft_strlen(file) - 4, 4) == 0)
		img = mlx_xpm_file_to_image(world->mlx, file, &width, &height);
	//if (ft_strncmp(".png", file + ft_strlen(file) - 4, 4) == 0)
	//	img = mlx_png_file_to_image(world->mlx, file, &width, &height);
	else
		error_throw("File is not .xpm or .png: %s", world, texture, file);
	if (!img)
		error_throw("Loading image failed: %s", world, texture, file);
	texture->width = width;
	texture->height = height;
	return (img);
}

void		process_texture_data(t_texture *texture, t_world *world)
{
	void	*img;
	char	*imgdata;
	int		bits_pp;
	int		linesize;

	img = texture->img;
	imgdata = mlx_get_data_addr(img, &bits_pp, &linesize, &(texture->endian));
	if (!imgdata)
		error_throw("Could not process texture data", world, img, NULL);
	texture->imgdata = (u_int32_t *)imgdata;
	texture->bytes_pp = bits_pp / 8;
	texture->linesize = linesize / texture->bytes_pp;
}

char		*texture_name(const char *file)
{
	char	*name;
	int		i;

	name = ft_strchr(file, '/') + 1;
	name = ft_substr(name, 0, ft_strchr(name, '.') - name);
	if (!name)
		return (NULL);
	i = 0;
	while (name[i])
	{
		name[i] = ft_toupper(name[i]);
		i++;
	}
	return (name);
}

t_texture	*load_texture(t_world *world, const char *file)
{
	t_texture	*tex;
	void		*img;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		error_throw("Out of memory", world, NULL, NULL);
	img = open_texture(world, (char *)file, tex);
	tex->img = img;
	tex->name = texture_name(file);
	if (!tex->name)
		error_throw("Texture not named: %s", world, tex, file);
	process_texture_data(tex, world);
	if (!tex->imgdata)
		error_throw("Could not process image data: %s", world, tex, file);
	ft_lstadd_back(&(world->l_textures), ft_lstnew(tex));
	return (tex);
}
