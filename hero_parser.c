/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:15:42 by lflorrie          #+#    #+#             */
/*   Updated: 2021/03/21 19:15:46 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"
#include <fcntl.h>
#include "math.h"

void	ft_free_map(t_map *map);
void print_map(t_map map);

t_hero	get_hero(t_map map)
{
	t_hero hero;
	int i;
	int j;

	i = 0;
	while (i < map.len_map)
	{
		j = 0;
		while (map.map[i][j] != '\0')
		{
			if (map.map[i][j] == 'S' || map.map[i][j] == 'N' || 
				map.map[i][j] == 'W' || map.map[i][j] == 'E')
			{
				hero.pos_x = i + 0.5;
				hero.pos_y = j + 0.5;
				break ;
			}
			++j;
		}
		++i;
	}
	double a = 0.25;
	hero.speed_x = a;
	hero.speed_y = a;
	hero.plane_x = 0.66;
	hero.plane_y = 0.66;
	if (map.map[(int)hero.pos_x][(int)hero.pos_y] == 'N')
	{
		hero.dir_x = -1;
		hero.dir_y = 0;
		hero.plane_x = 0;
		hero.plane_y = 0.66;
	}
	if (map.map[(int)hero.pos_x][(int)hero.pos_y] == 'S')
	{
		hero.dir_x = 1;
		hero.dir_y = 0;
		hero.plane_x = 0;
		hero.plane_y = -0.66;
	}
	if (map.map[(int)hero.pos_x][(int)hero.pos_y] == 'E')
	{
		hero.dir_x = 0;
		hero.dir_y = 1;
		hero.plane_x = 0.66;
		hero.plane_y = 0;
	}
	if (map.map[(int)hero.pos_x][(int)hero.pos_y] == 'W')
	{
		hero.dir_x = 0;
		hero.dir_y = -1;
		hero.plane_x = -0.66;
		hero.plane_y = 0;
	}
	return hero;
}

void	print_hero(t_hero hero)
{
	printf("\nHERO\n");
	printf("pos_x: %f pos_y: %f\n", hero.pos_x, hero.pos_y);
	printf("dir_x: %f dir_y: %f\n", hero.dir_x, hero.dir_y);
	printf("speed_x: %f speed_y: %f\n", hero.speed_x, hero.speed_y);
	printf("plane_x: %f plane_y: %f\n\n", hero.plane_x, hero.plane_y);

}

int	key_hook1(int keycode, t_vars *vars)
{
	double a = 0;

	printf("keycode: %i\n", keycode);
	if (keycode == KEY_W)
    {
    	if(vars->map.map[(int)(vars->hero.pos_x + vars->hero.dir_x * vars->hero.speed_x + a)][(int)(vars->hero.pos_y + a)] != '1')
    	{
    		vars->hero.pos_x  += vars->hero.dir_x * vars->hero.speed_x;
    	}
    	if(vars->map.map[(int)(vars->hero.pos_x + a)][(int)(vars->hero.pos_y + a + vars->hero.dir_y * vars->hero.speed_x + a)] != '1') vars->hero.pos_y += vars->hero.dir_y * vars->hero.speed_x;
    }
    //move backwards if no wall behind you
    if (keycode == KEY_S)
    {
      if(vars->map.map[(int)(vars->hero.pos_x - vars->hero.dir_x * vars->hero.speed_x + a)][(int)(vars->hero.pos_y + a)] != '1') vars->hero.pos_x  -= vars->hero.dir_x * vars->hero.speed_x;
      if(vars->map.map[(int)(vars->hero.pos_x + a)][(int)(vars->hero.pos_y - vars->hero.dir_y * vars->hero.speed_x + a)] != '1') vars->hero.pos_y -= vars->hero.dir_y * vars->hero.speed_x;
    }

    //rotate to the right
    if (keycode == KEY_D)
    {
      //both camera direction and camera plane must be rotated
      double old_dir_x = vars->hero.dir_x;
      vars->hero.dir_x = vars->hero.dir_x * cos(-vars->hero.speed_y) - vars->hero.dir_y * sin(-vars->hero.speed_y);
      vars->hero.dir_y = old_dir_x * sin(-vars->hero.speed_y) + vars->hero.dir_y * cos(-vars->hero.speed_y);
      double old_plane_x = vars->hero.plane_x;
      vars->hero.plane_x = vars->hero.plane_x * cos(-vars->hero.speed_y) - vars->hero.plane_y * sin(-vars->hero.speed_y);
      vars->hero.plane_y = old_plane_x * sin(-vars->hero.speed_y) + vars->hero.plane_y * cos(-vars->hero.speed_y);
    }
    //rotate to the left
    if (keycode == KEY_A)
    {
      //both camera direction and camera plane must be rotated
      double old_dir_x = vars->hero.dir_x;
      vars->hero.dir_x = vars->hero.dir_x * cos(vars->hero.speed_y) - vars->hero.dir_y * sin(vars->hero.speed_y);
      vars->hero.dir_y = old_dir_x * sin(vars->hero.speed_y) + vars->hero.dir_y * cos(vars->hero.speed_y);
      double old_plane_x = vars->hero.plane_x;
      vars->hero.plane_x = vars->hero.plane_x * cos(vars->hero.speed_y) - vars->hero.plane_y * sin(vars->hero.speed_y);
      vars->hero.plane_y = old_plane_x * sin(vars->hero.speed_y) + vars->hero.plane_y * cos(vars->hero.speed_y);
  	}
    raycasting(vars, &vars->map);
		
    print_hero(vars->hero);
    return (0);
}
void a(int argc, char **argv)
{
	//t_map	map;
	int		fd;
	//t_hero	hero;
	t_vars vars;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			perror("Failed!\n");
			exit (1);
		}
		vars.map = parser(fd);
		vars.hero = get_hero(vars.map);

		print_map(vars.map);
		print_hero(vars.hero);
		init_window(&vars, 1080, 1920);

		vars.img_frame = init_image(vars.mlx, vars.width, vars.height);
		vars.img_n = init_image_from_file(vars.mlx, vars.map.pict_north);
		vars.img_s = init_image_from_file(vars.mlx, vars.map.pict_south);
		vars.img_e = init_image_from_file(vars.mlx, vars.map.pict_east);
		vars.img_w = init_image_from_file(vars.mlx, vars.map.pict_west);

		mlx_hook(vars.win, 2, 1L<<0, key_hook1, &vars);
		raycasting(&vars, &vars.map);
		
		mlx_loop(vars.mlx);
		mlx_destroy_image(vars.mlx , &vars.img_frame);
		ft_free_map(&vars.map);
	}
}

int main(int argc, char **argv)
{	
	a(argc, argv);
	return (0);
}