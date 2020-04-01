/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 11:42:57 by brendan        #+#    #+#                */
/*   Updated: 2020/04/01 14:24:06 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "math.h"

static int	texture_x(t_ray *ray, t_texture *tex)
{
	double slice;

	if (ray->side == 'S' || ray->side == 'N')
		slice = ray->point[0] - ray->map_point[0];
	else if (ray->side == 'W' || ray->side == 'E')
		slice = ray->point[1] - ray->map_point[1];
	else
		slice = 0.0;
	if (ray->side == 'N' || ray->side == 'E')
		slice = 1.0 - slice;
	return ((int)(slice * tex->width));
}

static int	texture_y(int j, double dist, t_texture *tex, t_world *world)
{
	double	h;
	double	newj;

	newj = j - ((world->win_h / 2) * (1 - (1 / dist)));
	if (newj >= tex->height / 2)
		return ((int)ceil(tex->height * newj * dist / (double)world->win_h));
	else
		return ((int)(tex->height * newj * dist / (double)world->win_h));
}

static int	color_select(int y, int tex_x, t_ray *ray, t_world *world)
{
	int			tex_y;
	t_texture	*tex;

	tex = world->map->so_tex;
	tex_y = texture_y(y, ray->dist, tex, world);
	if (tex_y < 0)
		return (world->map->cl_color);
	else if (tex_y >= tex->height)
		return (world->map->fl_color);
	else
		return (tex->imgdata[tex_x + (tex_y * tex->linesize)]);
}

static void	render_column(unsigned long long i, t_ray *ray, t_world *world)
{
	t_texture	*screen;
	int 		j;
	double		height;
	int			tex_x;

	j = 0;
	screen = world->screen;
	tex_x = texture_x(ray, world->map->so_tex);
	while (j < world->win_h)
	{
		world->screen->imgdata[i] = color_select(j, tex_x, ray, world);
		j++;
		i += world->screen->linesize;
	}
}

void		render(t_world *world)
{
	t_ray	ray;
	double	raydir[4];	
	int		i;
	double	x;

	ft_memcpy(raydir, world->player->pos, 16);
	i = 0;
	while (i < world->win_w)
	{
		x = (double)(i - (world->win_w / 2)) / (double)(world->win_h);
		vec2_rot(raydir + 2, world->player->dir, 1.0, atan(x));
		cast_ray(raydir, &ray, world);
		ray.dist /= sqrt(1 + (x * x)); //fisheye correction
		render_column(i, &ray, world);
		i++;
	}
		mlx_put_image_to_window(world->mlx, world->window, \
							world->screen->img, 0, 0);
}
