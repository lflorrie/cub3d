#include "mlx.h"
#include <stdio.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_vars
{
	void *mlx;
	void *win;
	int width;
	int height;
	t_data img;
	t_data back_gr;
} t_vars;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void make_rainbow(t_vars vars, t_data *img)
{
	int i;
	int j;
	unsigned color;

	i = 0;
	color = 0x00654321;
	while (i < vars.width)
	{
		j = 0;
		while (j < vars.height)
		{
			my_mlx_pixel_put(img, i, j, color);
			++j;
		}
		++i;
	}
}


int				mouse_moving(t_vars *vars)
{
	int x, y;

    x = 0;
    y = 0;

	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	if (x < vars->width && y < vars->height && y > 0 && x > 0)
    {
    	mlx_mouse_hide(vars->mlx, vars->win);
    	mlx_put_image_to_window(vars->mlx, vars->win, vars->back_gr.img, 0, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, x, y);
    	printf("%d %d\n", x, y);
    	//mlx_destroy_image(vars->mlx, img.img);
    	//mlx_destroy_image(vars->mlx, vars->img.img);
    }
}

int main()
{
	t_vars vars;
	t_data img;

	vars.width = 800;
	vars.height = 600;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "TEST");

	// img.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// //make_rainbow(vars, &img);

	int img_width, img_height;
	//char *path = "./anime.xpm";
	char *path_cursor = "./cursor.xpm";



    char *path = "./anime.xpm";
	vars.back_gr.img = mlx_xpm_file_to_image(vars.mlx, path, &img_width, &img_height);
	
	mlx_loop_hook(vars.mlx, mouse_moving, &vars);
	
	vars.img.img = mlx_xpm_file_to_image(vars.mlx, path_cursor, &img_width, &img_height);
	// img.img = mlx_xpm_file_to_image(vars.mlx, path, &img_width, &img_height);
	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_destroy_image(vars.mlx, img.img);
	mlx_loop(vars.mlx);
	return (0);
}