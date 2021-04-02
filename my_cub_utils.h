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

typedef struct  s_hero {
        double  pos_x;
        double  pos_y;
        double  dir_x;
        double  dir_y;
        double  plane_x;
        double  plane_y;
        double  speed_x;
        double  speed_y;
        double  ray_dir_x;
        double  ray_dir_y;
        
}               t_hero;

typedef struct  s_map
{
        int     width;
        int     height;
        char    *pict_north;
        char    *pict_south;
        char    *pict_west;
        char    *pict_east;
        char    *pict_sprite;
        int     color_floor;
        int     color_ceil;
        char    **map;
        int     len_map;
}               t_map;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_image		img_n;
    t_image     img_s;
    t_image     img_e;
    t_image     img_w;
    t_map       map;
    t_hero      hero;
    t_image		img_frame;
}				t_vars;


#define KEY_RIGHT_ARROW 65363
#define KEY_LEFT_ARROW 65361
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307

// #define KEY_RIGHT_ARROW 124
// #define KEY_LEFT_ARROW 123
// #define KEY_W 13
// #define KEY_S 1
// #define KEY_A 0
// #define KEY_D 2
// #define KEY_ESC 53

void            my_mlx_pixel_put(t_image *data, int x, int y, int color);
char            *get_pixel(t_image *data, int x, int y);
void			init_window(t_vars *vars, int w, int h);
t_image			init_image(void *mlx, int w, int h);
t_image			init_image_from_file(void *mlx, char *path);
void			print_square(t_image *img, unsigned int color);
int				create_rgb(int r, int g, int b);

void	show_line(t_vars *vars, t_image *img, int start, int end, int h, int texX ,t_image *result);

void	raycasting(t_vars *vars, t_map *map);
t_map   parser(int fd);

int     proc_r(char *line, t_map *map);
int     proc_fc(char *line, t_map *map);
#endif