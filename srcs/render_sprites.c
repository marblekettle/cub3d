/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 12:54:35 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/24 18:06:04 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

static double	get_dist(t_list *list)
{
	return (-((t_obj *)(list->content))->relpos[0]);
}

void			obj_relpos(t_world *world)
{
	t_list	*list;
	double	vec[4];
	double	angle;

	list = world->l_objs;
	while (list)
	{
		vec[0] = ((t_obj *)(list->content))->pos[0] - world->player->pos[0];
		vec[1] = ((t_obj *)(list->content))->pos[1] - world->player->pos[1];
		angle = atan2(world->player->dir[1], world->player->dir[0]);
		vec2_rot(vec + 2, vec, 1.0, -angle);
		ft_memcpy(((t_obj *)(list->content))->relpos, vec + 2, 16);
		list = list->next;
	}
	list = world->l_objs;
	ft_lstsort(list, &get_dist);
}

void		clear_screen(t_texture *screen)
{
	long	i;

	i = 0;
	while (i < (screen->linesize * screen->height))
	{
		screen->imgdata[i] = 0x02000000;
		i++;
	}
}

U_INT		*get_pixel(t_texture *tex, int x, int y)
{
	if (x < tex->width && y < tex->height)
		return (&(tex->imgdata[x + (tex->linesize * y)]));
	else
		return (NULL);
}

U_INT		*get_pixel_scaled(t_texture *tex, double *point)
{
	int	pixel[2];

	pixel[0] = (int)(point[0] * tex->width);
	pixel[1] = (int)(point[1] * tex->height);
	if (pixel[0] >= tex->width)
		pixel[0] = tex->width - 1;
	if (pixel[1] >= tex->height)
		pixel[1] = tex->height - 1;
	return (get_pixel(tex, pixel[0], pixel[1]));
}

void		calculate_span(int *pixel, t_obj *obj, t_world *world)
{
	int		midpixel[2];
	int		newdim[2];
	double	offset;
	double	high;

	high = (double)(world->win_h);
	newdim[1] = high / obj->relpos[0];
	newdim[0] = high / obj->relpos[0];
	offset = obj->relpos[1] / obj->relpos[0];
	midpixel[0] = ((double)(world->win_w) / 2.0) + (offset * high);
	midpixel[1] = (high / 2.0);
	pixel[0] = (int)midpixel[0] - (high / 4.0 / obj->relpos[0]);
	pixel[1] = (int)midpixel[1] - (high / 2.0 / obj->relpos[0]);
	pixel[2] = (int)midpixel[0] + (high / 4.0 / obj->relpos[0]);
	pixel[3] = (int)midpixel[1] + (high / 2.0 / obj->relpos[0]);
}

void		obj_draw(t_obj *obj, char *mask, t_world *world)
{
	int		pixel[4];
	int		ipixel[2];
	double	scale[2];
	U_INT	*fromtex;

	calculate_span(pixel, obj, world);
	ipixel[0] = pixel[0] > 0 ? pixel[0] : 0;
	while (ipixel[0] < pixel[2] && ipixel[0] < world->win_w)
	{
		if (mask[ipixel[0]])
		{
			ipixel[1] = pixel[1] > 0 ? pixel[1] : 0;
			while (ipixel[1] < pixel[3] && ipixel[1] < world->win_h)
			{
				scale[0] = (double)(ipixel[0] - pixel[0]) / (double)(pixel[2] - pixel[0]);
				scale[1] = (double)(ipixel[1] - pixel[1]) / (double)(pixel[3] - pixel[1]);
				fromtex = get_pixel_scaled(obj->type->sprite, scale);
				if (*fromtex != obj->type->sprite->trans)
					*(get_pixel(world->screen[0], ipixel[0], ipixel[1])) = *fromtex;
				ipixel[1]++;
			}
		}
		ipixel[0]++;
	}
}

void		render_sprites(t_world *world, double *distarr)
{
	t_list	*iter;
	char	*mask;
	int		i;

	mask = malloc(sizeof(char) * world->win_w);
	iter = world->l_objs;
	while (iter && ((t_obj *)(iter->content))->relpos[0] > 0.0)
	{
		i = 0;
		while (i < world->win_w)
		{
			mask[i] = distarr[i] > ((t_obj *)(iter->content))->relpos[0] ? 1 : 0;
			i++;
		}
		obj_draw((t_obj *)(iter->content), mask, world);
		iter = iter->next;
	}
	free(mask);
}
