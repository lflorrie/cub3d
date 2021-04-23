/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:53:14 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 12:53:15 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

int	valid_around_space(char **arr, int i, int j, int len)
{
	if (i == 0)
		return (1);
	if (j == 0)
		return (1);
	if (i == len - 1)
		return (1);
	if ((int)ft_strlen(arr[i + 1]) < j || (int)ft_strlen(arr[i - 1]) < j)
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

int	validate_map_array(char **arr, int len)
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

int	double_initialized(t_map map, char c, char cc)
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

int	params_initialized(t_map map)
{
	if (map.width != 0 && map.height != 0
		&& map.pict_north != NULL && map.pict_south != NULL
		&& map.pict_west != NULL && map.pict_east != NULL
		&& map.pict_sprite != NULL && map.color_floor != -1
		&& map.color_ceil != -1)
		return (1);
	return (0);
}
