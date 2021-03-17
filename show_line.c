#include "my_cub_utils.h"


t_image change_size_image(void *mlx, t_image *img, int h)
{
	t_image new_image;

	double	coef_h = (double)h / img->height;
	double	coef_w = (double)w / img->width;
	new_image = init_image(mlx, w, h);
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		 {
		 	unsigned char *src = get_pixel(img, i / coef_w, j / coef_h);
			unsigned char b = src[0];
			unsigned char g = src[1];
			unsigned char r = src[2];
			my_mlx_pixel_put(&new_image, i, j, create_rgb(r, g, b));
		}
	}
	img->p_width = w;
	img->p_height = h;
	return (new_image);
}

void show_line(void *mlx, t_image img, int h)
{
		t_image img2;
		
		img2 = change_size_image(vars->mlx, &vars->img, vars->img.p_width, vars->img.p_height);
		mlx_put_image_to_window(vars->mlx, vars->win, img2.img, 0, 0);

		mlx_destroy_image(vars->mlx, img2.img);
}

int main()
{
	t_vars vars;
	t_image img;

	init_window(&vars, 800, 600);
	vars.img = init_image_from_file(vars.mlx, "anime.xpm");
	
	//mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}