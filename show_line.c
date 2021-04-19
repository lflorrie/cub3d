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
	double			tex_pos;
	unsigned char	*src;
	int				tex_y;

	step = 1.0 * (img->height - 1) / draws.line_h;
	tex_pos = (draws.draw_start - vars->height / 2 + draws.line_h / 2) * step;
	i = 0;
	img->p_height = draws.draw_end - draws.draw_start;
	while (i < draws.draw_start)
		my_mlx_pixel_put(&vars->img_frame, h, i++, vars->map.color_ceil);
	i = draws.draw_end;
	while (i < vars->height)
		my_mlx_pixel_put(&vars->img_frame, h, i++, vars->map.color_floor);
	i = 0;
	while (i <= draws.draw_end - draws.draw_start)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		src = (unsigned char *)get_pixel(img, draws.tex_x, tex_y);
		my_mlx_pixel_put(&vars->img_frame, h, i + draws.draw_start,
			create_rgb(src[2], src[1], src[0]));
		++i;
	}
}
