/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:14:24 by lflorrie          #+#    #+#             */
/*   Updated: 2021/03/29 23:14:25 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

int	feel_rgb(char **words, int (*rgb)[3], char **line, char *iter)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (i > 3)
			return (1);
		if (i < 3)
		{
			*line = ft_strtrim(words[i], " ");
			iter = *line;
			while (*iter)
			{
				if (!ft_isdigit(*iter))
					return (1);
				iter++;
			}
			(*rgb)[i] = ft_atoi(*line);
			if ((*rgb)[i] < 0 || (*rgb)[i] > 255)
				return (1);
			free(*line);
		}
		++i;
	}
	return (0);
}

int	proc_fc(char *line, t_map *map)
{
	char	**words;
	int		rgb[3];
	char	*iter;

	iter = line;
	++line;
	if ((*iter == 'F' && map->color_floor != -1)
		|| (*iter == 'C' && map->color_ceil != -1))
		return (1);
	words = ft_split(line, ',');
	if (!(words) || ft_count_words(line, ',') != 3)
		return (1);
	if (feel_rgb(words, &rgb, &line, iter))
	{
		ft_free_words(words);
		free(line);
		return (1);
	}
	if (*iter == 'F')
		map->color_floor = create_rgb(rgb[0], rgb[1], rgb[2]);
	if (*iter == 'C')
		map->color_ceil = create_rgb(rgb[0], rgb[1], rgb[2]);
	ft_free_words(words);
	return (0);
}
