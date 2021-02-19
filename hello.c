#include <mlx.h> 
#include <stdlib.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;
#include <math.h>

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
#include <stdio.h>
#include <math.h>
int     main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data    img;
    int width, height;

	
   width = 1920;
   height = 1080;    
    // width = 256;
    // height = 256;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, width, height, "Hello world!");
    img.img = mlx_new_image(mlx, width, height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    // 00
    //GOVNO
    int num = (0x00100000 - 0x00000000);
    size_t color1;
    //double colorstep = (0x00FF0000 - 0x00000000) / (double)width;
    double colorstep = (double)num / (double)width * 256;
    double cash = 0;
    for (int i = 0; i < width; ++i) { 
    	cash += colorstep;
    	color1 = (size_t)cash - ((size_t)cash % num);
    	if (i == 1)
    		printf("color1 = %.6lX\ncash = %.6lu	-	colorstep = %f\n ", color1, (size_t)cash, colorstep);
    	for (int j = 0; j < height; ++j) {
    			//if (sqrt(pow(i - width / 2, 2) + pow(j - height / 2, 2)) < (height / 2))
     			if ((i - width / 2) * (i - width / 2) + (j - height / 2) * (j - height / 2) <= height * height / 4)
     				my_mlx_pixel_put(&img, i, j, 0x000000F5);
     			else 
     				my_mlx_pixel_put(&img, i, j, color1);
    	}
    }
    

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}       

/*#include <mlx.h> 
int     main(void)
{
    void    *img;
    void    *mlx;

    mlx = mlx_init();
    img = mlx_new_image(mlx, 1920, 1080);
}
*/