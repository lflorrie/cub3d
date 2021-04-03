#include "my_cub_utils.h"

void	show_line(t_vars *vars, t_image *img, int start, int end, int h, int texX, t_image *result, int lineHeight)
{
	img->p_height = end - start;
	for (int i = 0; i < start; ++i)
	{
		my_mlx_pixel_put(result, h, i, vars->map.color_ceil);
	}
	for (int i = end; i < vars->height; ++i)
	{
		my_mlx_pixel_put(result, h, i, vars->map.color_floor);
	}
      // Starting texture coordinate
	double step = 1.0 * img->height / lineHeight;
	double texPos = (start - vars->height / 2 + lineHeight / 2) * step;
	for (int i = 0; i <= end - start; ++i)
	{
		int texY = (int)texPos ;
		texPos += step;
		unsigned char *src = (unsigned char *)get_pixel(img, texX, texY);
		
		unsigned char b = src[0];
		unsigned char g = src[1];
		unsigned char r = src[2];
		my_mlx_pixel_put(result, h, i + start, create_rgb(r, g, b));
	}
}