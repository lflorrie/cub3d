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

t_hero	init_hero(void)
{
	t_hero	hero;

	hero.speed_x = 0;
	hero.speed_y = 0;
	hero.plane_x = 0;
	hero.plane_y = 0;
	hero.dir_x = 0;
	hero.dir_y = 0;
	hero.pos_x = 0;
	hero.pos_y = 0;
	hero.ray_dir_x = 0;
	hero.ray_dir_y = 0;
	return (hero);
}

void	set_plane_and_dir(t_hero *hero, t_map map)
{
	if (map.map[(int)hero->pos_x][(int)hero->pos_y] == 'N')
	{
		hero->dir_x = -1;
		hero->plane_y = (map.width + 0.0) / map.height / 2;
	}
	if (map.map[(int)hero->pos_x][(int)hero->pos_y] == 'S')
	{
		hero->dir_x = 1;
		hero->plane_y = -((map.width + 0.0) / map.height / 2);
	}
	if (map.map[(int)hero->pos_x][(int)hero->pos_y] == 'E')
	{
		hero->dir_y = 1;
		hero->plane_x = (map.width + 0.0) / map.height / 2;
	}
	if (map.map[(int)hero->pos_x][(int)hero->pos_y] == 'W')
	{
		hero->dir_y = -1;
		hero->plane_x = -((map.width + 0.0) / map.height / 2);
	}
	hero->speed_x = 0.25;
	hero->speed_y = 0.25;
}

t_hero	get_hero(t_map map)
{
	t_hero	hero;
	int		i;
	int		j;

	hero = init_hero();
	i = -1;
	while (++i < map.len_map)
	{
		j = 0;
		while (map.map[i][j] != '\0')
		{
			if (map.map[i][j] == 'S' || map.map[i][j] == 'N' ||
				map.map[i][j] == 'W' || map.map[i][j] == 'E')
			{
				if (hero.pos_x != 0 || hero.pos_y != 0)
					return (hero);
				hero.pos_x = i + 0.5;
				hero.pos_y = j + 0.5;
			}
			++j;
		}
	}
	set_plane_and_dir(&hero, map);
	return (hero);
}
