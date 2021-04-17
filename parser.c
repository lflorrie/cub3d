/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:44:10 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 12:44:13 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"
#include <fcntl.h>

int		proc_texture(char *line, t_map *map)
{
	if (double_initialized(*map, *line, *(line + 1)))
		return (1);
	if (*line == 'N' && *(line + 1) == 'O')
		map->pict_north = ft_strtrim(line + 2, " ");
	else if (*line == 'S' && *(line + 1) == 'O')
		map->pict_south = ft_strtrim(line + 2, " ");
	else if (*line == 'W' && *(line + 1) == 'E')
		map->pict_west = ft_strtrim(line + 2, " ");
	else if (*line == 'E' && *(line + 1) == 'A')
		map->pict_east = ft_strtrim(line + 2, " ");
	else if (*line == 'S' && *(line + 1) != 'O')
		map->pict_sprite = ft_strtrim(line + 1, " ");
	else
		return (1);
	return (0);
}

int		is_image(void *mlx, char *pict)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, pict, &w, &h);
	if (img == NULL)
	{
		return (0);
	}
	mlx_destroy_image(mlx, img);
	return (1);
}

char	*parser(int fd, t_map *map)
{
	char	*line;
	char	*iter;
	int		error;

	error = 0;
	*map = init_map();
	while (get_next_line(fd, &line) > 0 && !error)
	{
		iter = ft_strtrim(line, " ");
		if (*iter == 'R')
		{
			if (proc_r(iter, map))
				return ("Error\nScreen resolution not correct.\n");
		}
		else if (*iter == 'F' || *iter == 'C')
		{
			if (proc_fc(iter, map))
				return ("Error\nFloor or ceiling not correct color.\n");
		}
		else if (*iter == 'N' || *iter == 'S' || *iter == 'W' || *iter == 'E')
		{
			if (proc_texture(iter, map))
				return ("Error\nProblems with texture\n");
		}
		else
			return ("Error\nNot valid flag\n");
		free(iter);
		free(line);
		line = NULL;
		if (params_initialized(*map))
			break ;
	}
	if (line)
		free(line);
	error += validate_map(map);
	if (error)
	{
		ft_free_map(map);
		exit(1);
	}
	if ((map->map = create_map(fd)) == NULL)
		return ("Error\nProblems with map\n");
	map->len_map = ft_array_len(map->map);
	if (validate_map_array(map->map, map->len_map))
	{
		printf("Error\nMap is not valid.\n");
		exit(1);
	}
	return ("");
}
