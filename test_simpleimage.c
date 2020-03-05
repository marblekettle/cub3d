/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_simpleimage.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:56:35 by bmans          #+#    #+#                */
/*   Updated: 2020/03/05 12:04:00 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libftprintf.h"

// 123 <- , 124 -> , 125 v , 126 ^

int g_posit[2] = {0, 0};

int		show_texture(void *world)
{
	t_world		*world_ptr;
	t_texture	*tex_ptr;
	int			x;
	int			y;
	int			col;

	world_ptr = (t_world *)world;
	mlx_clear_window(world_ptr->mlx, world_ptr->window);
	tex_ptr = (t_texture *)(world_ptr->l_textures->content);
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			col = get_texture_pixel(tex_ptr, x * tex_ptr->width / 100, y * tex_ptr->height / 100);
			mlx_pixel_put(world_ptr->mlx, world_ptr->window, x + g_posit[0], y + g_posit[1], col);
			x++;
		}
		y++;
	}
	return (1);
}

void	shutdown(t_world *world)
{
	ft_printf("Shutting down...\n");
	world_end(world);
	exit(0);
}

int		key_hook(int keycode, void *world)
{
//	ft_printf("%d\n", keycode);
	if (keycode == 53)
		shutdown(world);
	if (keycode == 123 && g_posit[0] > 0)
		g_posit[0] -= 10;
	if (keycode == 124 && g_posit[0] < 300)
		g_posit[0] += 10;
	if (keycode == 125 && g_posit[1] < 300)
		g_posit[1] += 10;
	if (keycode == 126 && g_posit[1] > 0)
		g_posit[1] -= 10;
	return (0);
}

int		main(void)
{
	t_world		*world;
	t_texture	*tex;

	world = world_init();
	if (world)
		ft_printf("World created successfully\n");
	if (!load_texture(world, "mick.png", &tex))
		ft_printf("Texture %s not loaded!\n", "mick.png");
	else
		ft_lstadd_back(&(world->l_textures), ft_lstnew(tex));
	world->window = mlx_new_window(world->mlx, 400, 400, "window");
	mlx_hook(world->window, 2, 0, &key_hook, world);
	mlx_loop_hook(world->mlx, &show_texture, world);
	mlx_loop(world->mlx);
	return (0);
}
