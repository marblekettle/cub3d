/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 11:42:57 by brendan       #+#    #+#                 */
/*   Updated: 2020/07/13 11:38:41 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "math.h"

static int	texture_x(t_ray *ray, t_texture *tex)
{
	double	slice;
	int		tex_x;

	if (ray->side == 'S' || ray->side == 'N')
		slice = ray->point[0] - ray->map_point[0];
	else if (ray->side == 'W' || ray->side == 'E')
		slice = ray->point[1] - ray->map_point[1];
	else
		slice = 0.0;
	if (ray->side == 'N' || ray->side == 'E')
		slice = 1.0 - slice;
	tex_x = (int)(slice * tex->width);
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static int	texture_y(int j, double dist, t_texture *tex, t_world *world)
{
	double	newj;

	newj = 0.99 * (j - (((world->win_h / 2)) * (1 - (1 / dist))));
	if (newj < 0.01)
		return (-1);
	else
		return ((int)(tex->height * newj * dist / (double)world->win_h));
}

static void	render_column(unsigned long long i, t_ray *ray, t_world *world)
{
	t_texture	*walltex;
	int			j;
	int			tex_x;
	int			tex_y;
	int			color;

	j = 0;
	if (ray->side == 'N' || ray->side == 'S')
		walltex = ray->side == 'N' ? world->map->no_tex : world->map->so_tex;
	else
		walltex = ray->side == 'W' ? world->map->we_tex : world->map->ea_tex;
	tex_x = texture_x(ray, walltex);
	while (j < world->win_h)
	{
		tex_y = texture_y(j, ray->dist, walltex, world);
		if (tex_y >= 0 && tex_y < walltex->height)
		{
			color = walltex->imgdata[tex_x + (tex_y * walltex->linesize)];
			world->screen[0]->imgdata[i] = color;
		}
		j++;
		i += world->screen[0]->linesize;
	}
}

static void	render_walls(t_world *world, double *distarr)
{
	t_ray	ray;
	double	raydir[4];
	int		i;
	double	x;

	ft_memcpy(raydir, world->player.pos, 16);
	i = 0;
	while (i < world->win_w)
	{
		x = 0.99 * (double)(i - (world->win_w / 2)) / (double)(world->win_h);
		vec2_rot(raydir + 2, world->player.dir, 1.0, atan(x));
		cast_ray(raydir, &ray, world);
		ray.dist /= sqrt(1 + (x * x));
		distarr[i] = ray.dist;
		render_column(i, &ray, world);
		i++;
	}
}

void		render(t_world *world, char to_window)
{
	double		*distarr;
	t_texture	*temp;

	obj_relpos(world);
	distarr = malloc(sizeof(double) * world->win_w);
	if (!distarr)
		error_throw("Out of memory", world, NULL, NULL);
	render_floor_ceiling(world);
	render_walls(world, distarr);
	render_sprites(world, distarr);
	if (to_window)
	{
		temp = world->screen[1];
		world->screen[1] = world->screen[0];
		world->screen[0] = temp;
		mlx_sync(1, world->screen[1]->img);
		mlx_put_image_to_window(world->mlx, world->window, \
								world->screen[1]->img, 0, 0);
		mlx_sync(3, world->window);
	}
	free(distarr);
}
