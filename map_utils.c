/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:48:26 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 12:48:30 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

char	**create_map(int fd)
{
	t_list	*map;
	char	*line;

	map = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (map == NULL)
			map = ft_lstnew(line);
		else
			ft_lstadd_back(&map, ft_lstnew(line));
		if (validate_map_line(line, map))
			return (NULL);
	}
	if (line)
	{
		ft_lstadd_back(&map, ft_lstnew(line));
		if (validate_map_line(line, map))
			return (NULL);
	}
	return (ft_list_to_array(map));
}

t_map	init_map(void)
{
	t_map map;

	map.width = 0;
	map.height = 0;
	map.color_floor = -1;
	map.color_ceil = -1;
	map.pict_north = NULL;
	map.pict_south = NULL;
	map.pict_west = NULL;
	map.pict_east = NULL;
	map.pict_sprite = NULL;
	map.map = NULL;
	map.len_map = 0;
	return (map);
}

void	ft_free_map(t_map *map)
{
	if (map->pict_north != NULL)
		free(map->pict_north);
	if (map->pict_south != NULL)
		free(map->pict_south);
	if (map->pict_west != NULL)
		free(map->pict_west);
	if (map->pict_east != NULL)
		free(map->pict_east);
	if (map->pict_sprite != NULL)
		free(map->pict_sprite);
	if (map->map != NULL)
	{
		while (map->len_map > 0)
		{
			free(map->map[map->len_map - 1]);
			--map->len_map;
		}
		free(map->map);
	}
}

int		validate_map(t_map *map)
{
	void	*mlx;
	int		h;
	int		w;

	mlx = mlx_init();
	mlx_get_screen_size(mlx, &w, &h);
	if (h < map->height)
		map->height = h;
	if (w < map->width)
		map->width = w;
	if (map->width == 0 || map->height == 0 || map->pict_north == NULL ||
		map->pict_south == NULL || map->pict_west == NULL ||
		map->pict_east == NULL || map->pict_sprite == NULL ||
		!is_image(mlx, map->pict_north) || !is_image(mlx, map->pict_south) ||
		!is_image(mlx, map->pict_west) || !is_image(mlx, map->pict_east) ||
		!is_image(mlx, map->pict_sprite))
	{
		free(mlx);
		printf("Error\nProblems with initializating.\n");
		return (1);
	}
	free(mlx);
	return (0);
}

int		validate_map_line(char *i, t_list *map)
{
	while (*i != '\0')
	{
		if (*i != ' ' && *i != '0' && *i != '1' && *i != '2' &&
			*i != 'N' && *i != 'S' && *i != 'W' && *i != 'E')
		{
			ft_lstclear(&map, free);
			return (1);
		}
		++i;
	}
	return (0);
}
