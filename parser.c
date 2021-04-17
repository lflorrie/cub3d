#include "my_cub_utils.h"
#include <fcntl.h>

int		double_initialized(t_map map, char c, char cc)
{
	if (c == 'N' && cc == 'O' && map.pict_north != NULL)
		return (1);
	if (c == 'S' && cc == 'O' && map.pict_south != NULL)
		return (1);
	if (c == 'W' && cc == 'E' && map.pict_west != NULL)
		return (1);
	if (c == 'E' && cc == 'A' && map.pict_east != NULL)
		return (1);
	if (c == 'S' && cc == ' ' && map.pict_sprite != NULL)
		return (1);
	return (0);
}

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

int		params_initialized(t_map map)
{
	if (map.width != 0 && map.height != 0 &&
	map.pict_north != NULL && map.pict_south != NULL &&
	map.pict_west != NULL && map.pict_east != NULL &&
	map.pict_sprite != NULL && map.color_floor != -1 &&
	map.color_ceil != -1)
		return (1);
	return (0);
}

int valid_around_space(char **arr, int i, int j, int len)
{
	if (i == 0)
		return (1);
	if (j == 0)
		return (1);
	if (i == len)
		return (1);
	if (ft_strlen(arr[i + 1]) < j || ft_strlen(arr[i - 1]) < j)
		return (1);
	if (arr[i - 1][j] == ' ')
		return (1);
	if (arr[i + 1][j] == ' ')
		return (1);
	if (arr[i][j - 1] == ' ')
		return (1);
	if (arr[i][j + 1] == ' ')
		return (1);
	return (0);
}

int		validate_map_array(char **arr, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S' ||
				arr[i][j] == 'E' || arr[i][j] == 'W' ||
				arr[i][j] == '0' || arr[i][j] == '2')
			{
				if (valid_around_space(arr, i, j, len))
					return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}

char		*parser(int fd, t_map *map)
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
				return("Error\nScreen resolution not correct.\n");
		}
		else if (*iter == 'F' || *iter == 'C')
		{
			if (proc_fc(iter, map))
				return("Error\nFloor or ceiling not correct color.\n");
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
	error += validate_map(map); //may be leaks
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
		printf("Error\nMap is not valid.\n"); // Problem with not static len of line
		exit(1);
	}
	return ("");
}