#include <stdio.h>
#include "my_cub_utils.h"
#include <math.h>

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned 	*)dst = color;
}

char	*get_pixel(t_image *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (dst);
}

t_image	init_image(void *mlx, int w, int h)
{
	t_image	img;

	img.width = w;
	img.height = h;
	img.img = mlx_new_image(mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.p_width = img.width;
	img.p_height = img.height;
	return (img);
}

t_image	init_image_from_file(void *mlx, char *path)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.p_width = img.width;
	img.p_height = img.height;
	return (img);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_window(t_vars *vars, int w, int h)
{
	vars->width = w;
	vars->height = h;
	vars->win = mlx_new_window(vars->mlx, vars->width,
			vars->height, "Cub3d_lflorrie");
}
