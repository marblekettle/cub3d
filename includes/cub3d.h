/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 14:33:23 by bmans          #+#    #+#                */
/*   Updated: 2020/03/05 14:22:19 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libftprintf.h"

typedef struct	s_world
{
	void		*mlx;
	void		*window;
	t_list		*l_textures;
	t_list		*l_maps;
}				t_world;

typedef struct	s_map
{
	char		**map;
}				t_map;

typedef struct	s_texture
{
	char		*name;
	int			linesize;
	int			width;
	int			height;
	int			bytes_pp;
	int			endian;
	U_INT		*imgdata;
}				t_texture;

char			file_exists(char *file);
int				get_texture_pixel(t_texture *texture, int x, int y);
void			*open_texture(t_world *world, char *file, t_texture *texture);
char			load_texture(t_world *world, char *file, t_texture **texture);
void			clear_texture(void *texture);
void			world_end(void *world);
t_world			*world_init(void);

#endif
