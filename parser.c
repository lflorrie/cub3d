#include "my_cub_utils.h"
#include <fcntl.h>

typedef struct	s_map
{
		int		width;
		int		height;
		char	*pict_north;
		char	*pict_south;
		char	*pict_west;
		char	*pict_east;
		char	*pict_sprite;
		int		color_floor;
		int		color_ceil;
		char	**map;
}				t_map;

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
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(iter);
		free(line);
	}
	free(line);
	error += validate_map(&map);
	if (error)
	{
		ft_free_map(&map);
		exit(1);
	}
	return (map);
}

int		*create_map(char *s)
{
	char **map;

	get_next_line( , )
	if (*s == ' ')
	if (*s == '1')
	if (*s == '0')
	if (*s == '0')
}

void print_map(t_map map)
{
	printf("\n--------------------\nPrint_map:\n");
	printf("R %d %d\n", map.width, map.height);
	printf("F %X\nC %X\n", map.color_floor, map.color_ceil);
	printf("NO %s\nSO %s\n", map.pict_north, map.pict_south);
	printf("WE %s\nEA %s\n", map.pict_west, map.pict_east);
	printf("S %s\n", map.pict_sprite);
}

int main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			perror("Failed!\n");
			exit (1);
		}
		map = parser(fd);
		print_map(map);
		ft_free_map(&map);
	}
	return (0);
}