#ifndef MY_CUB_UTILS_H
#define MY_CUB_UTILS_H
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <fcntl.h>
#include "math.h"

typedef struct	s_image {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int         p_width;
	int         p_height;
}               t_image;

typedef struct	s_hero {
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	speed_x;
		double	speed_y;
		double	ray_dir_x;
		double	ray_dir_y;
}				t_hero;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct  	s_map
{
		int     	width;
		int     	height;
		char    	*pict_north;
		char    	*pict_south;
		char    	*pict_west;
		char    	*pict_east;
		char    	*pict_sprite;
		int     	color_floor;
		int     	color_ceil;
		char    	**map;
		int     	len_map;
}               	t_map;

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
	t_sprite	*sprites;
	t_image     img_spr;
	int			num_sprites;
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

//#define KEY_RIGHT_ARROW 124
//#define KEY_LEFT_ARROW 123
//#define KEY_W 13
//#define KEY_S 1
//#define KEY_A 0
//#define KEY_D 2
//#define KEY_ESC 53

void            my_mlx_pixel_put(t_image *data, int x, int y, int color);
char            *get_pixel(t_image *data, int x, int y);
void			init_window(t_vars *vars, int w, int h);
t_image			init_image(void *mlx, int w, int h);
t_image			init_image_from_file(void *mlx, char *path);
void			print_square(t_image *img, unsigned int color);
int				create_rgb(int r, int g, int b);

void			show_line(t_vars *vars, t_image *img, int start, int end, int h, int texX ,t_image *result, int lineHeight);

void			raycasting(t_vars *vars, t_map *map);
char			*parser(int fd, t_map *map);
t_hero  		get_hero(t_map map);
char			**create_map(int fd);
t_map			init_map(void);
void    		ft_free_map(t_map *map);
int				validate_map_line(char *i, t_list *map);
int				validate_map(t_map *map);
int				validate_map_array(char **arr, int len);
int				double_initialized(t_map map, char c, char cc);
int				params_initialized(t_map map);
int     		proc_r(char *line, t_map *map);
int     		proc_fc(char *line, t_map *map);
int				get_num_sprites(t_map map);
void			init_sprites(t_vars *vars);
int				is_image(void *mlx, char *pict);
void			proc_w(t_vars *vars);
void			proc_s(t_vars *vars);
void			proc_a(t_vars *vars);
void			proc_d(t_vars *vars);
void			proc_key_r_arrow(t_vars *vars);
void			proc_key_l_arrow(t_vars *vars);
void			proc_key_esc(t_vars *vars);

void			show_sprite(t_vars *vars, t_image *img, int start, int end, int h, int texX, t_image *result, int lineHeight);
void			sort_sprites(int *order, double *dist, int amount);
#endif
