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
				hero.pos_x = i;
				hero.pos_y = j;
				break ;
			}
			++j;
		}
		++i;
	}
	hero.speed_x = 1;
	hero.speed_y = 1;
	hero.plane_x = 0;
	hero.plane_y = 0.66;
	if (map.map[(int)hero.pos_x][(int)hero.pos_y] == 'N')
	{
		hero.dir_x = 0;
		hero.dir_y = 1;
	}
	return hero;
}

void	print_hero(t_hero hero)
{
	printf("pos_x: %f pos_y: %f\n", hero.pos_x, hero.pos_y);
	printf("dir_x: %f dir_y: %f\n", hero.dir_x, hero.dir_y);
	
}

void a(int argc, char **argv)
{
	t_map	map;
	int		fd;
	t_hero	hero;
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			perror("Failed!\n");
			exit (1);
		}
		map = parser(fd);
		hero = get_hero(map);
		print_map(map);
		print_hero(hero);
		ft_free_map(&map);
	}
}

int main(int argc, char **argv)
{	
	a(argc, argv);
	return (0);
}