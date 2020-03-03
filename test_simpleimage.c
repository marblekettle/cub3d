/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_simpleimage.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:56:35 by bmans          #+#    #+#                */
/*   Updated: 2020/03/03 16:16:38 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libftprintf.h"

int	key_hook(int keycode, void *world)
{
	ft_printf("%d\n", keycode);
	if (keycode == 53)
	{
		
	}
	return (0);
}

int	main(void)
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
	world->window = mlx_new_window(world->mlx, 320, 320, "window");
	mlx_hook(world->window, 2, 0, &key_hook, world);
	mlx_loop(world->mlx);
	return (0);
}
