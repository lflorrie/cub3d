#include <stdio.h>
#include "my_cub_utils.h"
#include <math.h>
void            my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

char            *get_pixel(t_image *data, int x, int y)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    
    return dst;
}



t_image		init_image(void *mlx, int w, int h)
{
	t_image img;

	img.width = w;
	img.height = h;
	img.img = mlx_new_image(mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	img.p_width = img.width;
	img.p_height = img.height;
	return (img);
}

t_image		init_image_from_file(void *mlx, char *path)
{
	t_image img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	img.p_width = img.width;
	img.p_height = img.height;
	return (img);
}


void print_square(t_image *img, unsigned int color)
{
	// int j;
	// int i;

	// i = 0;
	// while (i < img->width)
	// {
	// 	j = 0;
	// 	while (j < img->height)
	// 	{
	// 		my_mlx_pixel_put(img, i, j, color);
	// 		++j;
	// 	}
	// 	++i;
	// }
	int j;
	int i;

	i = 0;
	int w = img->width / 3;
	while (i < w)
	{
		j = 0;
		while (j < img->height)
		{
			my_mlx_pixel_put(img, i, j, 0x00000055);
			++j;
		}
		++i;
	}
	unsigned char *src = (unsigned char*)get_pixel(img, 0, 0);
	unsigned char b = src[0];
	unsigned char g = src[1];
	unsigned char r = src[2];


	i = 2 * img->width / 3;
	w = 3 * img->width / 3;
	while (i < w)
	{
		j = 0;
		while (j < img->height)
		{
			my_mlx_pixel_put(img, i, j, 0x00FF0000);
			++j;
		}
		++i;
	}
	// unsigned char *src2 = get_pixel(img, img->width, 0);
	unsigned char *src2 = (unsigned char*)get_pixel(img, img->width - 1, 0);
	unsigned char b2 = src2[0];
	unsigned char g2 = src2[1];
	unsigned char r2 = src2[2];

	long long int blue = create_rgb(r, g, b);
	long long int yelllow = create_rgb(r2, g2, b2);
	
	long long int color_n = sqrt(blue * yelllow);

	i = img->width / 3;
	w = 2 * img->width / 3;
	while (i < w)
	{
		j = 0;
		while (j < img->height)
		{
			my_mlx_pixel_put(img, i, j, color_n);
			++j;
		}
		++i;
	}
	
}

void make_anime_girl(t_vars *vars, t_image *img)
{
	int w;
	int h;

	char *path = "anime.xpm";
	img->img = mlx_xpm_file_to_image(vars->mlx, path, &w, &h);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

// void make_mini_anime_girl(t_vars *vars, t_image *img, t_image *img2)
// {
// 	int a = 1;
// 	int aa = a - 1;
// 	for (int i = aa; i < vars->width / a - aa; ++i)
// 	{
// 		for (int j = aa; j < vars->height / a - aa; ++j)
// 		 {
// 			unsigned char *src = get_pixel(img, i * a, j * a);
// 			unsigned char b = src[0];
// 			unsigned char g = src[1];
// 			unsigned char r = src[2];
// 			int temp_r = r;
// 			int temp_g = g;
// 			int temp_b = b;
// 		 // 	for (int k = 0; k < a - 1; ++k)
// 		 // 	{
//  		// 		unsigned char *src2 = get_pixel(img, i * a - (a - k), j * a );
//  		// 		unsigned char b2 = src2[0];
//  		// 		unsigned char g2 = src2[1];
//  		// 		unsigned char r2 = src2[2];
// 			// 	temp_r += r2;
// 			// 	temp_g += g2;
// 			// 	temp_b += b2;
// 		 // 	}
// 		 // 	temp_r /= a;
// 		 // 	temp_g /= a;
// 		 // 	temp_b /= a;
// 		 // 	for (int k = 0; k < a - 1; ++k)
// 		 // 	{
//  		// 		unsigned char *src2 = get_pixel(img, i * a + k - 1, j * a);
//  		// 		unsigned char b2 = src2[0];
//  		// 		unsigned char g2 = src2[1];
//  		// 		unsigned char r2 = src2[2];
// 			// 	temp_r += r2;
// 			// 	temp_g += g2;
// 			// 	temp_b += b2;
// 		 // 	}
// 			// temp_r /= a;
// 		 // 	temp_g /= a;
// 		 // 	temp_b /= a;
// 		 // 	for (int k = 0; k < a - 1; ++k)
// 		 // 	{
//  		// 		unsigned char *src2 = get_pixel(img, i * a , j * a + k - 1);
//  		// 		unsigned char b2 = src2[0];
//  		// 		unsigned char g2 = src2[1];
//  		// 		unsigned char r2 = src2[2];
// 			// 	temp_r += r2;
// 			// 	temp_g += g2;
// 			// 	temp_b += b2;
// 		 // 	}
// 		 // 	temp_r /= a;
// 		 // 	temp_g /= a;
// 		 // 	temp_b /= a;
// 		 // 	for (int k = 0; k < a - 1; ++k)
// 		 // 	{
//  		// 		unsigned char *src2 = get_pixel(img, i * a , j * a - (a - k));
//  		// 		unsigned char b2 = src2[0];
//  		// 		unsigned char g2 = src2[1];
//  		// 		unsigned char r2 = src2[2];
// 			// 	temp_r += r2;
// 			// 	temp_g += g2;
// 			// 	temp_b += b2;
// 		 // 	}
// 		 // 	temp_r /= a;
// 		 // 	temp_g /= a;
// 		 // 	temp_b /= a;
// 			my_mlx_pixel_put(img2, i, j, create_rgb(temp_r, temp_g, temp_b));
// 		}
// 	}
// 	//mlx_put_image_to_window(vars->mlx, vars->win, img2->img, 0, 0);
// }


void init_window(t_vars *vars, int w, int h)
{
	vars->mlx = mlx_init();
	vars->width = w;
	vars->height = h;
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "Cub3d_lflorrie");
}

// int main(void)
// {
// 	t_vars vars;
// 	t_image img;
// 	t_image	img2;

// 	init_window(&vars, 800, 600);
// 	// //img = init_image_from_file(vars.mlx, "anime.xpm");
// 	img2 = init_image(vars.mlx, 800, 600);

// 	//print_square(&img, 0x000000FF);
// 	// make_anime_girl(&vars, &img);
// 	//print_square(&img, 0x000000FF);
// 	img = init_image_from_file(vars.mlx, "anime.xpm");
// 	make_mini_anime_girl(&vars, &img, &img2);
// 	mlx_put_image_to_window(vars.mlx, vars.win, img2.img, 0, 0);
// 	mlx_loop(vars.mlx);
// 	return (0);
// }

// int		main(void)
// {
// 	t_vars vars;
// 	t_image img;

// 	init_window(&vars, 800, 600);
// 	vars.img = init_image_from_file(vars.mlx, "anime.xpm");
// 	mlx_hook(vars.win, 2, 1L<<0, key_change_size_image, &vars);
// 	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
// 	//change_size_image(&vars, &img, 700, 500);
// 	mlx_loop(vars.mlx);
// 	return (0);
// }
