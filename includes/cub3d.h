/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 14:33:23 by bmans          #+#    #+#                */
/*   Updated: 2020/03/20 12:16:12 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libftprintf.h"

typedef struct	s_texture
{
	char		*name;
	int			linesize;
	int			width;
	int			height;
	int			bytes_pp;
	int			endian;
	void		*img;
	U_INT		*imgdata;
}				t_texture;

typedef struct	s_map
{
	char		**map;
	int			fl_color;
	int			cl_color;
	t_texture	*no_tex;
	t_texture	*so_tex;
	t_texture	*we_tex;
	t_texture	*ea_tex;
}				t_map;

typedef struct	s_world
{
	void		*mlx;
	void		*window;
	int			win_width;
	int			win_height;
	t_list		*l_textures;
	t_map		*map;
}				t_world;

char			file_exists(char *file);
int				get_texture_pixel(t_texture *texture, int x, int y);
void			*open_texture(t_world *world, char *file, t_texture *texture);
t_texture		*load_texture(t_world *world, char *file);
void			clear_texture(void *texture);
void			world_end(void *world);
void			error_throw(const char *err, t_world *world, void *tofree);
t_world			*world_init(void);
char			**ft_makearray(size_t len, ...);
void			ft_arraypush_front(char ***arr, char *new);
void			ft_arraypush_back(char ***arr, char *new);
size_t			ft_arraysize(char **arr);
void			ft_arrayclear(char ***arr);
t_map			*load_map(char *file, t_world *world);
void			draw_rect(int *coords, int color, t_world *world);
void			draw_line(int *coord, int color, t_world *world);

void			swap_int(int *a, int *b);
int	    		abs_int(int num);

#endif
