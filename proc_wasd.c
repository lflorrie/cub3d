/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_wasd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:04:04 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 12:04:08 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	proc_w(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)(vars->hero.pos_x + vars->hero.dir_x * vars->hero.speed_x);
	y = (int)(vars->hero.pos_y);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_x += vars->hero.dir_x * vars->hero.speed_x;
	x = (int)(vars->hero.pos_x);
	y = (int)(vars->hero.pos_y + vars->hero.dir_y * vars->hero.speed_x);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_y += vars->hero.dir_y * vars->hero.speed_x;
}

void	proc_s(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)(vars->hero.pos_x - vars->hero.dir_x * vars->hero.speed_x);
	y = (int)(vars->hero.pos_y);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_x -= vars->hero.dir_x * vars->hero.speed_x;
	x = (int)(vars->hero.pos_x);
	y = (int)(vars->hero.pos_y - vars->hero.dir_y * vars->hero.speed_x);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_y -= vars->hero.dir_y * vars->hero.speed_x;
}

void	proc_a(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)(vars->hero.pos_x);
	y = (int)(vars->hero.pos_y + vars->hero.dir_x * vars->hero.speed_x);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_y += vars->hero.dir_x * vars->hero.speed_x;
	x = (int)(vars->hero.pos_x - vars->hero.dir_y * vars->hero.speed_x);
	y = (int)(vars->hero.pos_y);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_x -= vars->hero.dir_y * vars->hero.speed_x;
}

void	proc_d(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)(vars->hero.pos_x);
	y = (int)(vars->hero.pos_y - vars->hero.dir_x * vars->hero.speed_x);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_y -= vars->hero.dir_x * vars->hero.speed_x;
	x = (int)(vars->hero.pos_x + vars->hero.dir_y * vars->hero.speed_x);
	y = (int)(vars->hero.pos_y);
	if (vars->map.map[x][y] != '1')
		vars->hero.pos_x += vars->hero.dir_y * vars->hero.speed_x;
}
