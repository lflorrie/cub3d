/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 20:35:27 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/06 20:35:29 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"
#include "stdlib.h"

void	ft_swap_i(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_d(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void sortSprites(int* order, double* dist, int amount)
{
	for (int i = 0; i < amount - 1; ++i)
	{
		for (int j = 0; j < amount - i - 1; ++i)
		{
			if (dist[j] > dist[j + 1])
			{
				ft_swap_i(order + j, order + j + 1);
				ft_swap_d(dist + j, dist + j + 1);
			}
		}
	}
}

int		get_num_sprites(t_map map)
{
	int		i;
	int		j;
	int		num_sprites;

	i = 0;
	num_sprites = 0;
	while (i < map.len_map)
	{
		j = 0;
		while (map.map[i][j] != '\0')
		{
			if (map.map[i][j] == '2')
				num_sprites++;
			++j;
		}
		++i;
	}
	return (num_sprites);
}

void		init_sprites(t_vars *vars)
{
	int			i;
	int			k;
	int			j;

	vars->num_sprites = get_num_sprites(vars->map);
	vars->sprites = (t_sprite*)malloc(sizeof(t_sprite) * vars->num_sprites);
	if (vars->sprites == NULL)
		return ;
	i = 0;
	k = 0;
	while (i < vars->map.len_map)
	{
		j = 0;
		while (vars->map.map[i][j] != '\0')
		{
			if (vars->map.map[i][j] == '2')
			{
				vars->sprites[k].x = i + 0.5;
				vars->sprites[k].y = j + 0.5;
				++k;
			}
			++j;
		}
		++i;
	}
}