#include "my_cub_utils.h"

t_image create_line(void *mlx, t_image *img, int w, int start, int end)
{
	t_image new_image;
	double	coef = (double)(end - start) / img->p_height;
	new_image = init_image(mlx, 1, 800);
	
	for (int i = 0; i < start; ++i)
	{
		my_mlx_pixel_put(&new_image, i, 0, 0x000000FF);
	}
	for (int i = end; i < 800; ++i)
	{
		my_mlx_pixel_put(&new_image, i, 0, 0x0011FF55);
	}
	for (int i = 0; i < end - start; ++i)
	{
	 	unsigned char *src = get_pixel(img, w, i / coef);
		unsigned char b = src[0];
		unsigned char g = src[1];
		unsigned char r = src[2];
		my_mlx_pixel_put(&new_image, i + start, 0, create_rgb(r, g, b));
	}
	return (new_image);
}

void show_line(t_vars *vars, t_image *img, int start, int end, int h)
{
		t_image img2;

		img2 = create_line(vars->mlx, img, h, start, end);
		mlx_put_image_to_window(vars->mlx, vars->win, img2.img, h, 0);

		mlx_destroy_image(vars->mlx, img2.img);
}

// int main()
// {
// 	t_vars vars;
// 	int h = 800;
// 	init_window(&vars, 800, 600);
// 	vars.img = init_image_from_file(vars.mlx, "anime.xpm");
// 	while (1)
// 		for (int i = 0; i < 100; ++i)
// 			show_line(&vars, &vars.img, i);	
// 	for (int i = 0; i < 120; ++i)
// 		show_line(&vars, &vars.img, i);	
// 	for (int i = 0; i < 500; ++i)
// 		show_line(&vars, &vars.img, i);	
// 	for (int i = 0; i < h; ++i)
// 		show_line(&vars, &vars.img, i);	
	
// 	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
// 	mlx_loop(vars.mlx);
// 	return (0);
// }