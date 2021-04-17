/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:57:30 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/17 17:57:32 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	show_line(t_vars *vars, t_image *img, t_draw draws, int h)
{
	int				i;
	double			step;
	double			texPos;
	unsigned char	*src;
	int				texY;

	step = 1.0 * img->height / draws.lineHeight;
	texPos = (draws.drawStart - vars->height / 2 + draws.lineHeight / 2) * step;
	i = 0;
	img->p_height = draws.drawEnd - draws.drawStart;
	while (i < draws.drawStart)
		my_mlx_pixel_put(&vars->img_frame, h, i++, vars->map.color_ceil);
	i = draws.drawEnd;
	while (i < vars->height)
		my_mlx_pixel_put(&vars->img_frame, h, i++, vars->map.color_floor);
	i = 0;
	while (i <= draws.drawEnd - draws.drawStart)
	{
		texY = (int)texPos;
		texPos += step;
		src = (unsigned char *)get_pixel(img, draws.texX, texY);
		my_mlx_pixel_put(&vars->img_frame, h, i + draws.drawStart,
			create_rgb(src[2], src[1], src[0]));
		++i;
	}
}
