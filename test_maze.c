/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_maze.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: brendan <brendan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 17:34:35 by brendan       #+#    #+#                 */
/*   Updated: 2020/06/16 13:22:45 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftprintf.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

double	g_pi = 3.1415927;
void	*g_mapwin = NULL;
t_world	*g_mapworld = NULL;

void	drawmapgrid(t_world *world)
{
	int		i;
	int		j;
	int		point[4];
	int		col;

	i = 0;
	while ((world->map->map)[i])
	{
		j = 0;
		while ((world->map->map)[i][j])
		{
			point[0] = (j * 40) + 2;
			point[1] = (i * 40) + 2;
			point[2] = ((j + 1) * 40) - 2;
			point[3] = ((i + 1) * 40) - 2;
			if ((world->map->map)[i][j] != ' ')
			{
				if ((world->map->map)[i][j] == '0')
					col = world->map->fl_color;
				if ((world->map->map)[i][j] == '1')
					col = world->map->cl_color;
				if ((world->map->map)[i][j] == 'S')
					col = 0x888888;
				draw_rect(point, point + 2, col, g_mapworld);
			}
			j++;
		}
		i++;
	}
}

void	drawmap(t_world *world)
{
	int		playpnt[6];
	int		raypnt[6];
	double	posdir[4];
	t_ray	*ray;

	mlx_clear_window(g_mapworld->mlx, g_mapworld->window);
	drawmapgrid(world);
	playpnt[0] = (int)((world->player->pos)[0] * 40) - 2;
	playpnt[1] = (int)((world->player->pos)[1] * 40) - 2;
	playpnt[2] = (int)((world->player->pos)[0] * 40) + 2;
	playpnt[3] = (int)((world->player->pos)[1] * 40) + 2;
	playpnt[4] = (int)((world->player->pos)[0] * 40);
	playpnt[5] = (int)((world->player->pos)[1] * 40);
	ft_memcpy(posdir, world->player->pos, 16);
	ft_memcpy(posdir + 2, world->player->dir, 16);
	draw_rect(playpnt, playpnt + 2, 0xFF0000, g_mapworld);
	ray = malloc(sizeof(t_ray));
	cast_ray(posdir, ray, world);
	raypnt[0] = (int)((ray->point)[0] * 40) - 2;
	raypnt[1] = (int)((ray->point)[1] * 40) - 2;
	raypnt[2] = (int)((ray->point)[0] * 40) + 2;
	raypnt[3] = (int)((ray->point)[1] * 40) + 2;
	raypnt[4] = (int)((ray->point)[0] * 40);
	raypnt[5] = (int)((ray->point)[1] * 40);
	draw_line(playpnt + 4, raypnt + 4, 0xFF0000, g_mapworld);
	draw_rect(playpnt, playpnt + 2, 0xFF0000, g_mapworld);
	draw_rect(raypnt, raypnt + 2, 0xFF0000, g_mapworld);
	free(ray);
}

int		shutdown(void *world)
{
	ft_printf("Shutting down...\n");
	world_end((t_world *)world);
	exit(0);
}

int		key_hook(int keycode, void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	if (keycode == 53 || keycode == 65307)
		shutdown(world);
	if ((keycode == 123 || keycode == 65361))
		vec2_rot(world->player->dir, world->player->dir, 1.0, -0.05);
	if ((keycode == 124 || keycode == 65363))
		vec2_rot(world->player->dir, world->player->dir, 1.0, 0.05);
	if ((keycode == 125 || keycode == 65364))
	{
		world->player->pos[0] -= world->player->dir[0] * 0.05;
		world->player->pos[1] -= world->player->dir[1] * 0.05;
	}
	if ((keycode == 126 || keycode == 65362))
	{
		world->player->pos[0] += world->player->dir[0] * 0.05;
		world->player->pos[1] += world->player->dir[1] * 0.05;
	}
//	drawmap(world);
	render(world);
	return (0);
}

/* int		loop_hook(void *world_ptr)
{
	t_world *world;

	world = (t_world *)world_ptr;
	vec2_rot(world->player->dir, world->player->dir, 1.0, 0.001);
	render(world);
} */

int		main(void)
{
	t_world	*world;
	t_map	*map;
	t_obj	*player;
	t_list	*list;

	world = world_init();
/*	g_mapwin = mlx_new_window(world->mlx, 400, 400, "map");
	g_mapworld = malloc(sizeof(t_world));
	g_mapworld->mlx = world->mlx;
	g_mapworld->window = g_mapwin; */
	ft_printf("Init successful\n");
	map = load_map("./test.cub", world);
	ft_printf("Map load successful\n");
//	printf("%s\n", world->map->so_tex->name);
	player = malloc(sizeof(t_obj));
	ft_memcpy(player->pos, world->map->init_pos, 16);
	ft_memcpy(player->dir, world->map->init_dir, 16);
	world->player = player;
	ft_printf("World prepared\n");
	prepare_window(world, "Labyrus vA0.01 - Powered by Loup3D");
	ft_printf("Window prepared\n");
	list = world->l_objs;
	while (list)
	{
		ft_printf("%d %d\n", (int)((t_obj *)(list->content))->pos[0], (int)((t_obj *)(list->content))->pos[1]);
		list = list->next;
	}
	render(world);
//	drawmap(world);
	mlx_hook(world->window, 2, 1L << 0, &key_hook, world);
	mlx_hook(world->window, 17, 0L, &shutdown, world);
//	mlx_key_hook(world->window, &key_hook, world);
//	mlx_loop_hook(world->mlx, &loop_hook, world);
	mlx_loop(world->mlx);
	return (0);
}