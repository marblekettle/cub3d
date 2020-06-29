/*
**	static int	darken(int color, double rate)
**	{
**	unsigned char	rgb[3];
**	int				out;
**
**	if (rate < 2.0)
**		return (color);
**	rgb[0] = (color & 0xFF0000) >> 16;
**	rgb[1] = (color & 0xFF00) >> 8;
**	rgb[2] = (color & 0xFF);
**	rgb[0] = (unsigned char)(rgb[0] * 2.0 / rate);
**	rgb[1] = (unsigned char)(rgb[1] * 2.0 / rate);
**	rgb[2] = (unsigned char)(rgb[2] * 2.0 / rate);
**	return (rgb[2] + (rgb[1] << 8) + (rgb[0] << 16));
**	}
*/

/*  static int	color_select(int y, int tex_x, t_ray *ray, t_world *world)
{
	int			tex_y;
	t_texture	*tex;

	if (ray->side == 'N' || ray->side == 'S')
		tex = ray->side == 'N' ? world->map->no_tex : world->map->so_tex;
	else
		tex = ray->side == 'W' ? world->map->we_tex : world->map->ea_tex;
	tex_y = texture_y(y, ray->dist, tex, world);
	if (tex_y < 0)
		return (world->map->cl_color);
	else if (tex_y >= tex->height)
		return (world->map->fl_color);
	else

	if (tex_y >= 0 && tex_y < tex->height)
		return (tex->imgdata[tex_x + (tex_y * tex->linesize)]);
} */

/*  void	prepare_screen(t_texture **screen, int *dim, t_world *world)
{
	void		*img;
	t_texture	*newscreen;

	img = mlx_new_image(world->mlx, dim[0], dim[1]);
	if (!img)
		error_throw("Could not create screen image", world, NULL, NULL);
	newscreen = malloc(sizeof(t_texture));
	if (!newscreen)
		error_throw("Out of memory", world, img, NULL);
	ft_bzero(newscreen, sizeof(t_texture));
	newscreen->img = img;
	newscreen->width = dim[0];
	newscreen->height = dim[1];
	process_texture_data(newscreen, world);
	*screen = newscreen;
}

void	prepare_window(t_world *world, const char *name)
{
	int		dim[2];
	char	i;

	dim[0] = world->win_w;
	dim[1] = world->win_h;
	world->window = mlx_new_window(world->mlx, dim[0], dim[1], (char *)name);
	if (!world->window)
		error_throw("Could not create window: %s", world, NULL, name);
	i = 0;
	while (i < 2)
	{
		prepare_screen(world->screen + i, dim, world);
		i++;
	}
} */