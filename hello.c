#include <mlx.h> 
#include <stdlib.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
// int     main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_data    img;
//     int width, height;

	
//    width = 1920;
//    height = 1080;    
//     // width = 256;
//     // height = 256;
//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, width, height, "Hello world!");
//     img.img = mlx_new_image(mlx, width, height);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//                                  &img.endian);
//     // 00
//     //GOVNO
//     int num = (0x00100000 - 0x00000000);
//     size_t color1;
//     //double colorstep = (0x00FF0000 - 0x00000000) / (double)width;
//     double colorstep = (double)num / (double)width * 256;
//     double cash = 0;
//     for (int i = 0; i < width; ++i) { 
//     	cash += colorstep;
//     	color1 = (size_t)cash - ((size_t)cash % num);
//     	if (i == 1)
//     		printf("color1 = %.6lX\ncash = %.6lu	-	colorstep = %f\n ", color1, (size_t)cash, colorstep);
//     	for (int j = 0; j < height; ++j) {
//     			//if (sqrt(pow(i - width / 2, 2) + pow(j - height / 2, 2)) < (height / 2))
//      			if ((i - width / 2) * (i - width / 2) + (j - height / 2) * (j - height / 2) <= height * height / 4)
//      				my_mlx_pixel_put(&img, i, j, 0x000000F5);
//      			else 
//      				my_mlx_pixel_put(&img, i, j, color1);
//     	}
//     }
    

//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_loop(mlx);
// }       

#include <mlx.h>
#include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    int			height;
    int			width;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	if (keycode == 65307) /*Escape*/
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
}


int				key_hook(int keycode, t_vars *vars) {
	printf("%d\n", keycode);
}
int g_lol = 0;
int xx = 0;
int yy = 0;
int				mouse_moving(t_vars *vars)
{
	int x, y;

    x = 0;
    y = 0;

	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	if (g_lol == 1 &&x < vars->width && y < vars->height && y > 0 && x > 0)
    {
    	xx = x;
    	yy = y;
    	g_lol = 0;
    	printf("%d %d\n", x, y);
    }
}

int             red_cross_clicked(int keycode, t_vars vars)
{
	int x = 0;
   	int y = 0;
   	if (keycode == 1)
   		g_lol = 1;
	//mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);  
   	if (xx < yy)
   	{
   	}
		printf("%d\n", keycode);
	return 0;
}

int             main(void)
{
    t_vars      vars;

   	int x = 0;
   	int y = 0;

    vars.width = 640;
    vars.height = 480;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "Hello world!");
   	
   	//red_cross
  	mlx_mouse_hook(vars.win, red_cross_clicked, &vars);
    mlx_loop_hook(vars.mlx, mouse_moving, &vars);
    
    mlx_loop(vars.mlx);
} 