#include "my_cub_utils.h"

void	show_line(t_vars *vars, t_image *img, int start, int end, int h, int texX, t_image *result)
{
	double	coef = (double)(end - start) / img->height;

	for (int i = 0; i < start; ++i)
	{
		my_mlx_pixel_put(result, h, i, vars->map.color_ceil);
	}
	for (int i = end; i < vars->height; ++i)
	{
		my_mlx_pixel_put(result, h, i, vars->map.color_floor);
	}
	for (int i = 0; i <= end - start; ++i)
	{
	 	unsigned char *src = (unsigned char *)get_pixel(img, texX, i / coef);
		unsigned char b = src[0];
		unsigned char g = src[1];
		unsigned char r = src[2];
		my_mlx_pixel_put(result, h, i + start, create_rgb(r, g, b));
	}
	img->p_width = texX;
	img->p_height = end - start;
}