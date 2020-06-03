/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 14:33:23 by bmans         #+#    #+#                 */
/*   Updated: 2020/05/21 16:08:16 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef MAX_DIST
#  define MAX_DIST 20.0
# endif
# include "libftprintf.h"

typedef struct	s_texture
{
	char			*name;
	int				linesize;
	int				width;
	int				height;
	int				bytes_pp;
	int				endian;
	void			*img;
	U_INT			*imgdata;
}					t_texture;

typedef struct	s_map
{
	char			**map;
	int				fl_color;
	int				cl_color;
	double			init_pos[2];
	double			init_dir[2];
	t_texture		*no_tex;
	t_texture		*so_tex;
	t_texture		*we_tex;
	t_texture		*ea_tex;
}					t_map;


typedef struct		s_actor
{
	double			pos[2];
	double			dir[2];
	double			rad;
	t_texture		*sprite;

}					t_actor;

typedef struct		s_world
{
	void			*mlx;
	void			*window;
	int				win_w;
	int				win_h;
	t_texture		*screen;
	t_list			*l_textures;
	t_map			*map;
	t_actor			*player;
}					t_world;

typedef struct		s_ray
{
	double			dist;
	double			point[2];
	int				map_point[2];
	char			side;
	char			content;
	struct s_ray	*next;
}					t_ray;

t_texture			*load_texture(t_world *world, const char *file);
void				clear_texture(t_world *world, t_texture *texture);
void				clear_texture_list(t_world *world, t_list *lst);
void				process_texture_data(t_texture *texture, t_world *world);
void				world_end(void *world);
void				error_throw(const char *err, t_world *world, \
							void *tofree, const char *file);
t_world				*world_init(void);
char				**ft_makearray(size_t len, ...);
void				ft_arraypush_front(char ***arr, char *new);
void				ft_arraypush_back(char ***arr, char *new);
size_t				ft_arraysize(char **arr);
void				ft_arrayclear(char ***arr);
char				ft_arrayfind(int *spot, char *term, char **arr);

t_map				*load_map(char *file, t_world *world);
char			    check_prefix(char *str, t_map *map, t_world *world);

void				draw_rect(int *ul_point, int *lr_point, int color, \
													t_world *world);
void				draw_line(int *s_point, int *e_point, int color, \
													t_world *world);

void				cast_ray(double *pos_dir, t_ray *ray, t_world *world);

void		 		vec2_join(int *vecout, int *vec1, int *vec2);
void				vec2_rot(double *out, double *in, double r, double theta);

void				prepare_window(t_world *world, const char *name);
void				render(t_world *world);

void				swap_int(int *a, int *b);
int	    			abs_int(int num);
double				sign(double num);

#endif
