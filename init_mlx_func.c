/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:39:31 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 18:39:37 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	init_window(t_vars *vars, int w, int h)
{
	vars->width = w;
	vars->height = h;
	vars->win = mlx_new_window(vars->mlx, vars->width,
			vars->height, "Cub3d_lflorrie");
}

t_image	init_image(void *mlx, int w, int h)
{
	t_image	img;

	img.width = w;
	img.height = h;
	img.img = mlx_new_image(mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.p_width = img.width;
	img.p_height = img.height;
	return (img);
}

t_image	init_image_from_file(void *mlx, char *path)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.p_width = img.width;
	img.p_height = img.height;
	return (img);
}
