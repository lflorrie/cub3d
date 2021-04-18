/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:52:00 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/18 17:52:02 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

void	show_sprite_y(t_vars *vars, t_draw_sprite *d_s, int x)
{
	int				d;
	int				y;
	unsigned char	*src;

	y = d_s->draw_start_y;
	while (y < d_s->draw_end_y)
	{
		d = (y) * 256 - vars->height * 128 + d_s->sprite_h * 128;
		d_s->tex_y = ((d * vars->img_spr.height) / d_s->sprite_h) / 256;
		if (d_s->tex_y >= 0 && d_s->tex_x >= 0)
		{
			src = (unsigned char *)get_pixel(&vars->img_spr,
					d_s->tex_x, d_s->tex_y);
			if (src[3] != 255)
				my_mlx_pixel_put(&vars->img_frame, x, y,
					create_rgb(src[2], src[1], src[0]));
		}
		++y;
	}
}

void	show_sprite(t_vars *vars, t_draw_sprite d_s,
			int sprite_w, double *p_buffer)
{
	int				x;

	x = d_s.draw_start_x;
	while (x < d_s.draw_end_x)
	{
		d_s.tex_x = (int)(256 * (x - (-sprite_w / 2 + d_s.sprite_screen_x
						)) * vars->img_spr.width / sprite_w) / 256;
		if (d_s.tr_y > 0 && x > 0 && x < vars->width && d_s.tr_y < p_buffer[x])
		{
			show_sprite_y(vars, &d_s, x);
		}
		++x;
	}
}

void	draw_sprite(t_vars *vars, t_draw_sprite dr_spr,
					double *p_buffer)
{
	int				sprite_w;
	int				d;
	unsigned char	*src;

	sprite_w = abs((int)(vars->height / (dr_spr.tr_y)));
	dr_spr.draw_start_x = -sprite_w / 2 + dr_spr.sprite_screen_x;
	if (dr_spr.draw_start_x < 0)
		dr_spr.draw_start_x = 0;
	dr_spr.draw_end_x = sprite_w / 2 + dr_spr.sprite_screen_x;
	if (dr_spr.draw_end_x >= vars->width)
		dr_spr.draw_end_x = vars->width - 1;
	show_sprite(vars, dr_spr, sprite_w, p_buffer);
}

void	calc_and_draw_sprite(t_vars *v, t_draw_sprite *d_s, int *sprite_order,
			double *p_buffer)
{
	double	sp_x;
	double	sp_y;
	double	i_d;
	double	tr_x;
	int		i;

	i = 0;
	while (i < v->num_sprites)
	{
		sp_x = v->sprites[sprite_order[i]].x - v->hero.pos_x;
		sp_y = v->sprites[sprite_order[i++]].y - v->hero.pos_y;
		i_d = 1.0 / (v->hero.plane_x * v->hero.dir_y - v->hero.dir_x
				* v->hero.plane_y);
		tr_x = i_d * (v->hero.dir_y * sp_x - v->hero.dir_x * sp_y);
		d_s->tr_y = i_d * (-v->hero.plane_y * sp_x + v->hero.plane_x * sp_y);
		d_s->sprite_screen_x = (int)((v->width / 2) * (1 + tr_x / d_s->tr_y));
		d_s->sprite_h = abs((int)(v->height / (d_s->tr_y)));
		d_s->draw_start_y = -d_s->sprite_h / 2 + v->height / 2;
		if (d_s->draw_start_y < 0)
			d_s->draw_start_y = 0;
		d_s->draw_end_y = d_s->sprite_h / 2 + v->height / 2;
		if (d_s->draw_end_y >= v->height)
			d_s->draw_end_y = v->height - 1;
		draw_sprite(v, *d_s, p_buffer);
	}
}

void	sprite_raycast(t_vars *vars, double *p_buffer)
{
	int				*sprite_order;
	double			*sprite_distance;
	t_draw_sprite	dr_spr;

	init_sprite_array(vars, &sprite_order, &sprite_distance);
	sort_sprites(sprite_order, sprite_distance, vars->num_sprites);
	calc_and_draw_sprite(vars, &dr_spr, sprite_order, p_buffer);
	destroy_sprite_array(&sprite_order, &sprite_distance);
}
