#include <stdio.h>
#include "my_cub_utils.h"
#include <math.h>

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned *)dst = color;
}

char	*get_pixel(t_image *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (dst);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
