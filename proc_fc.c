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
