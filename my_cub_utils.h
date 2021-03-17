#ifndef MY_CUB_UTILS_H
#define MY_CUB_UTILS_H
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct  s_image {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int			width;
    int			height;

    int         p_width;
    int         p_height;
}               t_image;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_image		img;
}				t_vars;

#define KEY_RIGHT_ARROW 65363
#define KEY_LEFT_ARROW 65361
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307

void            my_mlx_pixel_put(t_image *data, int x, int y, int color);
char            *get_pixel(t_image *data, int x, int y);
void			init_window(t_vars *vars, int w, int h);
t_image			init_image(void *mlx, int w, int h);
t_image			init_image_from_file(void *mlx, char *path);
void			print_square(t_image *img, unsigned int color);
int				create_rgb(int r, int g, int b);

#endif