/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp_screen_shot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:04:04 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/18 18:04:05 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"
#include <stdio.h>

t_bit_map_inf	get_bit_info(int w, int h)
{
	t_bit_map_inf bih;

	bih.bi_size = sizeof(t_bit_map_inf);
	bih.bi_width = w;
	bih.bi_height = h;
	bih.bi_planes = 1;
	bih.bi_bit_counts = 24;
	bih.bi_size_image = bih.bi_width * bih.bi_height * 3;
	bih.bi_compression = 0;
	bih.bi_x_pels_per_meter = 2835;
	bih.bi_y_pels_per_meter = 2835;
	bih.bi_clr_used = 0;
	bih.bi_clr_important = 0;
	return (bih);
}

t_bit_map	get_bit_file(t_bit_map_inf bih)
{
	t_bit_map bfh;

	bfh.bf_type = 0x4D42;
	bfh.bf_reserved1 = 0;
	bfh.bf_reserved2 = 0;
	bfh.bf_size = sizeof(t_bit_map) + sizeof(t_bit_map_inf) +
		bih.bi_width * bih.bi_height * 3;
	bfh.bf_off_bits = sizeof(t_bit_map) + bih.bi_size;
	return (bfh);
}

void	screen_shot(t_vars *vars)
{
	t_bit_map_inf	bih;
	t_bit_map		bfh;

	bih = get_bit_info(vars->width, vars->height);
	bfh = get_bit_file(bih);
	FILE *f;
	f = fopen("test.bmp","w+");

	fwrite(&bfh, sizeof(t_bit_map), 1, f);
	fwrite(&bih, sizeof(t_bit_map_inf), 1, f);

	unsigned char *s;


	int i,j;

	for(i = 0; i < bih.bi_height; i++)
	{
		for(j = 0; j < bih.bi_width; j++)
		{
			s = (unsigned char *)get_pixel(&vars->img_frame, i, j);
			fwrite(s, 3, 1, f);
		}
	}
	fclose(f);
}