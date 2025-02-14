/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 14:33:23 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/13 10:35:21 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef WINDOW_TITLE
#  define WINDOW_TITLE "Cub3D"
# endif
# ifndef SCREENSHOT_NAME
#  define SCREENSHOT_NAME "./save.bmp"
# endif
# ifndef TRANS_COLOR
#  define TRANS_COLOR 0xFFFF
# endif
# include "libftprintf.h"

typedef struct	s_texture
{
	char		*name;
	int			linesize;
	int			width;
	int			height;
	int			bytes_pp;
	int			endian;
	u_int32_t	trans;
	void		*img;
	u_int32_t	*imgdata;
}				t_texture;

typedef struct	s_map
{
	char		**map;
	int			fl_color;
	int			cl_color;
	double		init_pos[2];
	double		init_dir[2];
	t_texture	*no_tex;
	t_texture	*so_tex;
	t_texture	*we_tex;
	t_texture	*ea_tex;
}				t_map;

typedef	struct	s_objtype
{
	char		id;
	double		rad;
	t_texture	*sprite;
}				t_objtype;

typedef struct	s_obj
{
	double		pos[2];
	double		dir[2];
	double		relpos[2];
	t_objtype	*type;
}				t_obj;

typedef struct	s_control
{
	char		keypress;
}				t_control;

typedef struct	s_config
{
	char		**config_file;
	u_int8_t	set;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*path_s;
}				t_config;

typedef struct	s_world
{
	void		*mlx;
	void		*window;
	int			win_w;
	int			win_h;
	t_texture	*screen[2];
	t_control	control;
	t_config	config;
	t_obj		player;
	t_list		*l_textures;
	t_list		*l_objtypes;
	t_list		*l_objs;
	t_map		*map;

}				t_world;

typedef struct	s_ray
{
	double		dist;
	double		point[2];
	int			map_point[2];
	char		side;
	char		content;
}				t_ray;

t_texture		*load_texture(t_world *world, const char *file);
void			clear_texture(t_world *world, t_texture *texture);
void			clear_texture_list(t_world *world, t_list *lst);
char			*texture_name(const char *file);
void			process_texture_data(t_texture *texture, t_world *world);
void			world_end(t_world *world);
void			error_throw(const char *err, t_world *world, \
							void *tofree, const char *file);
void			world_init(t_world *world);
char			**ft_makearray(size_t len, ...);
void			ft_arraypush_front(char ***arr, char *new);
void			ft_arraypush_back(char ***arr, char *new);
size_t			ft_arraysize(char **arr);
void			ft_arrayclear(char ***arr);
char			ft_arrayfind(int *spot, char *term, char **arr);
int				**ft_arraysearch(char term, char **arr);
void			load_map(char *file, t_world *world);
void			cast_ray(double *pos_dir, t_ray *ray, t_world *world);
void			vec2_join(int *vecout, int *vec1, int *vec2);
void			vec2_rot(double *out, double *in, double r, double theta);
void			prepare_window(t_world *world, const char *name);
void			render(t_world *world, char to_window);
u_int32_t		*get_pixel(t_texture *tex, int *pixel);
u_int32_t		*get_pixel_scaled(t_texture *tex, float *point);
void			render_floor_ceiling(t_world *world);
void			check_map(char **map, t_world *world);
void			new_obj(t_objtype *objtype, int *pos, t_world *world);
void			move_player(t_world *world, char dir, double speed);
void			save_bitmap(t_texture *image, t_world *world, char *name);
void			prepare_screen(t_world *world);
void			swap_int(int *a, int *b);
int				abs_int(int num);
double			sign(double num);
void			obj_relpos(t_world *world);
void			render_sprites(t_world *world, double *distarr);
void			ft_lstsort(t_list *list, double (*crit)(t_list *));
void			prepare_loop_hooks(t_world *world);
void			config_action(char index, char *line, t_world *world);
void			process_map_tex(t_map *map, t_world *world);
void			process_sprite(const char *file, t_world *world);
void			process_objs(t_map *map, t_world *world);

#endif
