/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:48:21 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/02 16:48:24 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"
int	key_hook(int keycode, t_vars *vars)
{
	// printf("keycode: %i\n", keycode);
	if (keycode == KEY_W)
	{
		if(vars->map.map[(int)(vars->hero.pos_x + vars->hero.dir_x * vars->hero.speed_x)][(int)(vars->hero.pos_y)] != '1')
			vars->hero.pos_x  += vars->hero.dir_x * vars->hero.speed_x;
		if(vars->map.map[(int)(vars->hero.pos_x)][(int)(vars->hero.pos_y + vars->hero.dir_y * vars->hero.speed_x)] != '1')
			vars->hero.pos_y += vars->hero.dir_y * vars->hero.speed_x;
	}
	if (keycode == KEY_S)
	{
		if(vars->map.map[(int)(vars->hero.pos_x - vars->hero.dir_x * vars->hero.speed_x)][(int)(vars->hero.pos_y)] != '1')
			vars->hero.pos_x  -= vars->hero.dir_x * vars->hero.speed_x;
		if(vars->map.map[(int)(vars->hero.pos_x)][(int)(vars->hero.pos_y - vars->hero.dir_y * vars->hero.speed_x)] != '1')
			vars->hero.pos_y -= vars->hero.dir_y * vars->hero.speed_x;
	}
	if (keycode == KEY_A)
	{
		if(vars->map.map[(int)(vars->hero.pos_x)][(int)(vars->hero.pos_y + vars->hero.dir_x * vars->hero.speed_x)] != '1')
			vars->hero.pos_y += vars->hero.dir_x * vars->hero.speed_x;
		if(vars->map.map[(int)(vars->hero.pos_x - vars->hero.dir_y * vars->hero.speed_x)][(int)(vars->hero.pos_y)] != '1')
			vars->hero.pos_x -= vars->hero.dir_y * vars->hero.speed_x;
	}
	if (keycode == KEY_D)
	{
		if(vars->map.map[(int)(vars->hero.pos_x)][(int)(vars->hero.pos_y - vars->hero.dir_x * vars->hero.speed_x)] != '1')
			vars->hero.pos_y -= vars->hero.dir_x * vars->hero.speed_x;
		if(vars->map.map[(int)(vars->hero.pos_x + vars->hero.dir_y * vars->hero.speed_x)][(int)(vars->hero.pos_y)] != '1')
			vars->hero.pos_x += vars->hero.dir_y * vars->hero.speed_x;
	}
	if (keycode == KEY_RIGHT_ARROW)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = vars->hero.dir_x;
		vars->hero.dir_x = vars->hero.dir_x * cos(-vars->hero.speed_y) - vars->hero.dir_y * sin(-vars->hero.speed_y);
		vars->hero.dir_y = old_dir_x * sin(-vars->hero.speed_y) + vars->hero.dir_y * cos(-vars->hero.speed_y);
		double old_plane_x = vars->hero.plane_x;
		vars->hero.plane_x = vars->hero.plane_x * cos(-vars->hero.speed_y) - vars->hero.plane_y * sin(-vars->hero.speed_y);
		vars->hero.plane_y = old_plane_x * sin(-vars->hero.speed_y) + vars->hero.plane_y * cos(-vars->hero.speed_y);
    }
	if (keycode == KEY_LEFT_ARROW)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = vars->hero.dir_x;
		vars->hero.dir_x = vars->hero.dir_x * cos(vars->hero.speed_y) - vars->hero.dir_y * sin(vars->hero.speed_y);
		vars->hero.dir_y = old_dir_x * sin(vars->hero.speed_y) + vars->hero.dir_y * cos(vars->hero.speed_y);
		double old_plane_x = vars->hero.plane_x;
		vars->hero.plane_x = vars->hero.plane_x * cos(vars->hero.speed_y) - vars->hero.plane_y * sin(vars->hero.speed_y);
		vars->hero.plane_y = old_plane_x * sin(vars->hero.speed_y) + vars->hero.plane_y * cos(vars->hero.speed_y);
	}
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		
		ft_free_map(&vars->map);
		//mlx_destroy_image(vars-1>mlx, &vars->img_frame);
		exit(0);
	}
	raycasting(vars, &vars->map);
	return (0);
}

int main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;
	char	*errors;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			printf("Error!\nFile not exist.\n");
			exit (1);
		}
		errors = parser(fd, &vars.map);
		if (ft_strlen(errors) != 0)
		{
			printf(errors);
			return (1);
		}
		// print_map(vars.map);
		vars.hero = get_hero(vars.map);
		init_window(&vars, vars.map.width, vars.map.height);

		vars.img_frame = init_image(vars.mlx, vars.width, vars.height);
		vars.img_n = init_image_from_file(vars.mlx, vars.map.pict_north);
		vars.img_s = init_image_from_file(vars.mlx, vars.map.pict_south);
		vars.img_e = init_image_from_file(vars.mlx, vars.map.pict_east);
		vars.img_w = init_image_from_file(vars.mlx, vars.map.pict_west);
		mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
		raycasting(&vars, &vars.map);
		mlx_loop(vars.mlx);
		mlx_destroy_image(vars.mlx , &vars.img_frame);
		ft_free_map(&vars.map);
	}
	return (0);
}