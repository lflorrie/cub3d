/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:41:03 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/18 14:41:05 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

int	calc_texture(t_vars *vars, t_draw *draws, int img_width)
{
	double	wallX;
	int		tex_x;

	if (draws->side == 0)
		wallX = vars->hero.pos_y + draws->perp_wall_dist * vars->hero.ray_dir_y;
	else
		wallX = vars->hero.pos_x + draws->perp_wall_dist * vars->hero.ray_dir_x;
	wallX -= floor((wallX));
	tex_x = (int)(wallX * (double)img_width);
	if (draws->side == 0 && vars->hero.ray_dir_x > 0)
		tex_x = img_width - tex_x - 1;
	if (draws->side == 1 && vars->hero.ray_dir_y < 0)
		tex_x = img_width - tex_x - 1;
	return (tex_x);
}

void	step_and_sidedist(t_vars *vars, t_draw *draws)
{
	if (vars->hero.ray_dir_x < 0)
	{
		draws->step_x = -1;
		draws->side_dist_x = (vars->hero.pos_x
				- draws->map_x) * draws->delta_dist_x;
	}
	else
	{
		draws->step_x = 1;
		draws->side_dist_x = (draws->map_x + 1.0
				- vars->hero.pos_x) * draws->delta_dist_x;
	}
	if (vars->hero.ray_dir_y < 0)
	{
		draws->step_y = -1;
		draws->side_dist_y = (vars->hero.pos_y
				- draws->map_y) * draws->delta_dist_y;
	}
	else
	{
		draws->step_y = 1;
		draws->side_dist_y = (draws->map_y + 1.0
				- vars->hero.pos_y) * draws->delta_dist_y;
	}
}

void	dda(t_vars *vars, t_map *map, t_draw *draws)
{
	while ((map->map[draws->map_x][draws->map_y]) != '1')
	{
		if (draws->side_dist_x < draws->side_dist_y)
		{
			draws->side_dist_x += draws->delta_dist_x;
			draws->map_x += draws->step_x;
			draws->side = 0;
		}
		else
		{
			draws->side_dist_y += draws->delta_dist_y;
			draws->map_y += draws->step_y;
			draws->side = 1;
		}
	}
	if (draws->side == 0)
		draws->perp_wall_dist = (draws->map_x - vars->hero.pos_x
				+ (1 - draws->step_x) / 2) / vars->hero.ray_dir_x;
	else
		draws->perp_wall_dist = (draws->map_y - vars->hero.pos_y
				+ (1 - draws->step_y) / 2) / vars->hero.ray_dir_y;
	if (draws->perp_wall_dist == 0)
		draws->perp_wall_dist = 0.1;
	draws->line_h = (int)(vars->height / draws->perp_wall_dist);
}

void	draw_walls(t_vars *vars, t_draw *draws, int x)
{
	if (vars->hero.ray_dir_x < 0 && draws->side == 0)
	{
		draws->tex_x = calc_texture(vars, draws, vars->img_n.width);
		show_line(vars, &vars->img_n, *draws, x);
	}
	if (vars->hero.ray_dir_x > 0 && draws->side == 0)
	{
		draws->tex_x = calc_texture(vars, draws, vars->img_s.width);
		show_line(vars, &vars->img_s, *draws, x);
	}
	if (vars->hero.ray_dir_y < 0 && draws->side == 1)
	{
		draws->tex_x = calc_texture(vars, draws, vars->img_w.width);
		show_line(vars, &vars->img_w, *draws, x);
	}
	if (vars->hero.ray_dir_y > 0 && draws->side == 1)
	{
		draws->tex_x = calc_texture(vars, draws, vars->img_e.width);
		show_line(vars, &vars->img_e, *draws, x);
	}
}
