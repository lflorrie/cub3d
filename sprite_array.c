/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:53:24 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/18 17:53:26 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	init_sprite_array(t_vars *vars, int **sprite_order,
			double **sprite_distance)
{
	int	i;

	*sprite_order = (int *)malloc(sizeof(int) * vars->num_sprites);
	*sprite_distance = (double *)malloc(sizeof(double) * vars->num_sprites);
	if (*sprite_order == NULL || *sprite_distance == NULL)
		return ;
	i = 0;
	while (i < vars->num_sprites)
	{
		(*sprite_order)[i] = i;
		(*sprite_distance)[i] = ((vars->hero.pos_x - vars->sprites[i].x)
				* (vars->hero.pos_x - vars->sprites[i].x) + (vars->hero.pos_y
					- vars->sprites[i].y) * (vars->hero.pos_y
					- vars->sprites[i].y));
		++i;
	}
}

void	destroy_sprite_array(int **sprite_order, double **sprite_distance)
{
	if (*sprite_order)
		free(*sprite_order);
	if (*sprite_distance)
		free(*sprite_distance);
}
