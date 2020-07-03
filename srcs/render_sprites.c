/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 12:54:35 by bmans         #+#    #+#                 */
/*   Updated: 2020/07/03 13:29:24 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static double	get_dist(t_list *list)
{
	return (-((t_obj *)(list->content))->relpos[0]);
}

static void		calculate_span(int *pixel, t_obj *obj, t_world *world)
{
	int		midpixel[2];
	int		newdim[2];
	double	offset;
	double	high;
	double	ratio;

	high = (double)(world->win_h);
	ratio = (double)(obj->type->sprite->width);
	ratio /= (double)(obj->type->sprite->height);
	newdim[1] = high / obj->relpos[0];
	newdim[0] = (int)(newdim[1] * ratio);
	offset = obj->relpos[1] / obj->relpos[0];
	midpixel[0] = ((double)(world->win_w) / 2.0) + (offset * high);
	midpixel[1] = (high / 2.0);
	pixel[0] = (int)midpixel[0] - (newdim[0] / 2.0);
	pixel[1] = (int)midpixel[1] - (newdim[1] / 2.0);
	pixel[2] = (int)midpixel[0] + (newdim[0] / 2.0);
	pixel[3] = (int)midpixel[1] + (newdim[1] / 2.0);
}

static void		obj_draw(t_obj *obj, char *mask, t_world *world)
{
	int			pix[6];
	float		scale[2];
	u_int32_t	*fromtex;

	calculate_span(pix, obj, world);
	pix[4] = pix[0] > 0 ? pix[0] : 0;
	scale[0] = (float)(pix[4] - pix[0]) / (float)(pix[2] - pix[0]);
	while (pix[4] < pix[2] && pix[4] < world->win_w)
	{
		if (mask[pix[4]])
		{
			pix[5] = pix[1] > 0 ? pix[1] : 0;
			scale[1] = (float)(pix[5] - pix[1]) / (float)(pix[3] - pix[1]);
			while (pix[5] < pix[3] && pix[5] < world->win_h)
			{
				fromtex = get_pixel_scaled(obj->type->sprite, scale);
				if (*fromtex != obj->type->sprite->trans)
					*(get_pixel(&(world->screen), pix + 4)) = *fromtex;
				scale[1] += 1.0 / (float)(pix[3] - pix[1]);
				pix[5]++;
			}
		}
		scale[0] += 1.0 / (float)(pix[2] - pix[0]);
		pix[4]++;
	}
}

void			obj_relpos(t_world *world)
{
	t_list	*list;
	double	vec[4];
	double	angle;

	list = world->l_objs;
	while (list)
	{
		vec[0] = ((t_obj *)(list->content))->pos[0] - world->player.pos[0];
		vec[1] = ((t_obj *)(list->content))->pos[1] - world->player.pos[1];
		angle = atan2(world->player.dir[1], world->player.dir[0]);
		vec2_rot(vec + 2, vec, 1.0, -angle);
		ft_memcpy(((t_obj *)(list->content))->relpos, vec + 2, 16);
		list = list->next;
	}
	list = world->l_objs;
	ft_lstsort(list, &get_dist);
}

void			render_sprites(t_world *world, double *distarr)
{
	t_list	*iter;
	char	*mask;
	double	objdist;
	int		i;

	mask = malloc(sizeof(char) * world->win_w);
	iter = world->l_objs;
	while (iter && ((t_obj *)(iter->content))->relpos[0] > 0.0)
	{
		objdist = ((t_obj *)(iter->content))->relpos[0];
		i = 0;
		while (i < world->win_w)
		{
			mask[i] = distarr[i] > objdist;
			i++;
		}
		obj_draw((t_obj *)(iter->content), mask, world);
		iter = iter->next;
	}
	free(mask);
}
