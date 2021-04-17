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

int	proc_texture(char *line, t_map *map)
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

int	is_image(void *mlx, char *pict)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, pict, &w, &h);
	if (img == NULL)
		return (0);
	mlx_destroy_image(mlx, img);
	return (1);
}

char	*pars(char *iter, t_map *map)
{
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
	return (NULL);
}

char	*validate_and_create_map(void *mlx, t_map *map, int fd)
{
	char	*err_message;

	err_message = validate_map(mlx, map);
	if (err_message != NULL)
	{
		ft_free_map(map);
		return ("Error\nMap is not valid.\n");
	}
	map->map = create_map(fd);
	if (map->map == NULL)
		return ("Error\nProblems with map\n");
	map->len_map = ft_array_len(map->map);
	if (validate_map_array(map->map, map->len_map))
	{
		ft_free_map(map);
		return ("Error\nMap is not valid.\n");
	}
	return (NULL);
}

char	*parser(void *mlx, int fd, t_map *map)
{
	char	*line;
	char	*iter;
	char	*err_message;

	*map = init_map();
	while (get_next_line(fd, &line) > 0)
	{
		iter = ft_strtrim(line, " ");
		err_message = pars(iter, map);
		if (err_message)
			return (err_message);
		free(iter);
		free(line);
		line = NULL;
		if (params_initialized(*map))
			break ;
	}
	if (line)
		free(line);
	err_message = validate_and_create_map(mlx, map, fd);
	if (err_message)
		return (err_message);
	return ("");
}
