/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:20:53 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 12:20:56 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	proc_key_r_arrow(t_vars *vars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->hero.dir_x;
	old_plane_x = vars->hero.plane_x;
	vars->hero.dir_x = vars->hero.dir_x * cos(-vars->hero.speed_y)
		- vars->hero.dir_y * sin(-vars->hero.speed_y);
	vars->hero.dir_y = old_dir_x * sin(-vars->hero.speed_y)
		+ vars->hero.dir_y * cos(-vars->hero.speed_y);
	vars->hero.plane_x = vars->hero.plane_x * cos(-vars->hero.speed_y)
		- vars->hero.plane_y * sin(-vars->hero.speed_y);
	vars->hero.plane_y = old_plane_x * sin(-vars->hero.speed_y)
		+ vars->hero.plane_y * cos(-vars->hero.speed_y);
}

void	proc_key_l_arrow(t_vars *vars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->hero.dir_x;
	old_plane_x = vars->hero.plane_x;
	vars->hero.dir_x = vars->hero.dir_x * cos(vars->hero.speed_y)
		- vars->hero.dir_y * sin(vars->hero.speed_y);
	vars->hero.dir_y = old_dir_x * sin(vars->hero.speed_y)
		+ vars->hero.dir_y * cos(vars->hero.speed_y);
	vars->hero.plane_x = vars->hero.plane_x * cos(vars->hero.speed_y)
		- vars->hero.plane_y * sin(vars->hero.speed_y);
	vars->hero.plane_y = old_plane_x * sin(vars->hero.speed_y)
		+ vars->hero.plane_y * cos(vars->hero.speed_y);
}

void	proc_key_esc(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	ft_free_map(&vars->map);
	//mlx_destroy_image(vars-1>mlx, &vars->img_frame);
	exit(0);
}
