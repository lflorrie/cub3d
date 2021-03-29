#include "my_cub_utils.h"
#include <fcntl.h>

int		ft_array_len(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return (i);
	while (arr[i] != NULL)
		++i;
	return (i);
}

int		proc_r(char *line, t_map *map)
{
	char	*temp;

	++line;
	line = ft_strtrim(line, " ");
	temp = line;
	map->width = ft_atoi(line);
	while (ft_isdigit(*line))
		++line;
	while (*line == ' ')
		++line;
	map->height = ft_atoi(line);
	while (ft_isdigit(*line))
		++line;
	if (map->height <= 0 || map-> width <= 0 || *line != '\0')
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

void	ft_free_words(char **ar)
{
	int i;

	i = 0;
	while (ar[i] != NULL)
	{
		free(ar[i]);
		++i;
	}
	free(ar);
}

static int	ft_count_words(const char *s, char c)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i + 1] == c || s[i + 1] == '\0')
			++len;
		++i;
	}
	return (len);
}

int		proc_fc(char *line, t_map *map)
{
	char	flag;
	char	**words;
	int		i;
	int		rgb[3];
	char	*iter;

	i = 0;
	flag = *line;
	++line;
	if (!(words = ft_split(line, ',')) || ft_count_words(line, ',') != 3)
		return (1);
	while (words[i] != NULL)
	{
		if (i < 3)
		{
			line = ft_strtrim(words[i], " ");
			iter = line;
			while (*iter)
			{
				if (!ft_isdigit(*iter))
				{
					ft_free_words(words);
					free(line);
					return (1);
				}
				iter++;
			}
			rgb[i] = ft_atoi(line);
			free(line);
		}
		++i;
	}
	ft_free_words(words);
	if (i != 3)
		return (1);
	while (i > 0)
	{
		--i;
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
	}
	if (flag == 'F')
		map->color_floor = create_rgb(rgb[0], rgb[1], rgb[2]);
	if (flag == 'C')
		map->color_ceil = create_rgb(rgb[0], rgb[1], rgb[2]);
	return (0);
}

void	proc_texture(char *line, t_map *map)
{
	if (*line == 'N' && *(line + 1) == 'O')
		map->pict_north = ft_strtrim(line + 2, " ");
	if (*line == 'S' && *(line + 1) == 'O')
		map->pict_south = ft_strtrim(line + 2, " ");
	if (*line == 'W' && *(line + 1) == 'E')
		map->pict_west = ft_strtrim(line + 2, " ");
	if (*line == 'E' && *(line + 1) == 'A')
		map->pict_east = ft_strtrim(line + 2, " ");
	if (*line == 'S' && *(line + 1) != 'O')
		map->pict_sprite = ft_strtrim(line + 1, " ");
}

t_map	init_map()
{
	t_map map;

	map.width = 0;
	map.height = 0;
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
		free (map->pict_north);
	if (map->pict_south != NULL)
		free (map->pict_south);
	if (map->pict_west != NULL)
		free (map->pict_west);
	if (map->pict_east != NULL)
		free (map->pict_east);
	if (map->pict_sprite != NULL)
		free (map->pict_sprite);
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
		mlx_destroy_image(mlx, img);
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

char	**list_to_array(t_list *lst)
{
	t_list	*temp;
	int		size;
	int		i;
	char	**arr;

	i = 0;
	if ((size = ft_lstsize(lst)) == 0)
		return (NULL);
	if (!(arr = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		arr[i] = (char*)lst->content;
		temp = lst;
		lst = lst->next;
		free(temp);
		++i;
	}
	arr[size] = NULL;
	return (arr);
}

int		validate_map_line(char *i, t_list *map)
{
	while (*i != '\0')
	{
		if (*i != ' ' && *i != '0' && *i != '1' &&
			*i != 'N' && *i != 'S' && *i != 'W' && *i != 'E')
		{
			ft_lstclear(&map, free);
			printf("Error\nProblems with map. Symbol %c\n", *i);
			return (1);
		}
		++i;
	}
	return (0);
}

char	**create_map(int	fd)
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
	return (list_to_array(map));
}

void print_map(t_map map)
{
	printf("\n--------------------\nPrint_map:\n");
	printf("R %d %d\n", map.width, map.height);
	printf("F %X\nC %X\n", map.color_floor, map.color_ceil);
	printf("NO %s\nSO %s\n", map.pict_north, map.pict_south);
	printf("WE %s\nEA %s\n", map.pict_west, map.pict_east);
	printf("S %s\n", map.pict_sprite);
	if (map.map != NULL)
		printf("Len = %i\n", map.len_map);
	for (int j = 0; j < map.len_map; ++j)
	{
		printf("%s\n", map.map[j]);
	}
}

int		params_initialized(t_map map)
{
	if (map.width != 0 && map.height != 0 &&
	map.pict_north != NULL && map.pict_south != NULL &&
	map.pict_west != NULL && map.pict_east != NULL &&
	map.pict_sprite != NULL)
		return (1);
	return (0);
}
int		validate_map_array(char **arr)
{
	int	i;
	int	j;
	int	now_max;

	i = 0;
	now_max = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (j > now_max)
			{
				now_max = j;
				if (arr[i][j] != '1')
					return (1);
			}
		}
	}
	return (0);
}

t_map	parser(int fd)
{
	t_map	map;
	char	*line;
	char	*iter;
	int		error;

	error = 0;
	map = init_map();
	while (get_next_line(fd, &line) > 0 && !error)
	{
		iter = ft_strtrim(line, " ");
		if (*iter == 'R')
		{
			if (proc_r(iter, &map))
			{
				printf("Error\nScreen resolution not correct.\n");
				error = 1;
			}
		}	
		if (*iter == 'F' || *iter == 'C')
			if (proc_fc(iter, &map))
			{
				printf("Error\nFloor or ceiling not correct color.\n");
				error = 1;
			}
		if (*iter == 'N' || *iter == 'S' || *iter == 'W' || *iter == 'E')
			proc_texture(iter, &map);
		free(iter);
		free(line);
		line = NULL;
		if (params_initialized(map))
			break ;
	}
	if (line)
		free(line);
	//error += validate_map(&map);
	if (error)
	{
	 	ft_free_map(&map);
	 	exit(1);
	}
	map.map = create_map(fd);
	map.len_map = ft_array_len(map.map);
	// if (validate_map_array(map.map))
	// 	exit(1);
	return (map);
}

// void main(int argc, char **argv)
// {
// 	t_map	map;
// 	int		fd;

// 	if (argc == 2)
// 	{
// 		if ((fd = open(argv[1], O_RDONLY)) == -1)
// 		{
// 			perror("Failed!\n");
// 			exit (1);
// 		}
// 		map = parser(fd);
// 		
// 		print_map(map);
// 		ft_free_map(&map);
// 	}
// }
