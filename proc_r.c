/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:10:29 by lflorrie          #+#    #+#             */
/*   Updated: 2021/03/29 23:10:31 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	overflow(int *h, int *w)
{
	if (*h == -1)
		*h = 10000000;
	if (*w == -1)
		*w = 10000000;
}

int	proc_r(char *line, t_map *map)
{
	char	*temp;

	if (map->width != 0 || map->height != 0)
		return (1);
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
	overflow(&map->height, &map->width);
	if (map->height <= 0 || map->width <= 0 || *line != '\0')
	{
		free(temp);
		return (1);
	}
	free(temp);
	map->screen_width = map->width;
	map->screen_height = map->height;
	return (0);
}
