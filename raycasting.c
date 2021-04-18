#include "my_cub_utils.h"
#include "math.h"

void	show_sprite(t_vars *vars, t_draw_sprite dr_spr,
			int sprite_w, double p_buffer[vars->width])
{
	int				x;
	int				y;
	int				d;
	unsigned char	*src;

	x = dr_spr.draw_start_x;
	while (x < dr_spr.draw_end_x)
	{
		dr_spr.tex_x = (int)(256 * (x - (-sprite_w / 2 + dr_spr.sprite_screen_x
						)) * vars->img_spr.width / sprite_w) / 256;
		if (dr_spr.transform_y > 0 && x > 0 && x < vars->width
			&& dr_spr.transform_y < p_buffer[x])
		{
			y = dr_spr.draw_start_y;
			while (y < dr_spr.draw_end_y)
			{
				d = (y) * 256 - vars->height * 128 + dr_spr.sprite_h * 128;
				dr_spr.tex_y = ((d * vars->img_spr.height)
						/ dr_spr.sprite_h) / 256;
				if (dr_spr.tex_y >= 0 && dr_spr.tex_x >= 0)
				{
					src = (unsigned char *)get_pixel(&vars->img_spr,
							dr_spr.tex_x, dr_spr.tex_y);
					if (src[3] != 255)
						my_mlx_pixel_put(&vars->img_frame, x, y,
							create_rgb(src[2], src[1], src[0]));
				}
				++y;
			}
		}
		++x;
	}
}

void	draw_sprite(t_vars *vars, t_draw_sprite dr_spr,
					double p_buffer[vars->width])
{
	int				sprite_w;
	int				d;
	unsigned char	*src;

	sprite_w = abs((int)(vars->height / (dr_spr.transform_y)));
	dr_spr.draw_start_x = -sprite_w / 2 + dr_spr.sprite_screen_x;
	if (dr_spr.draw_start_x < 0)
		dr_spr.draw_start_x = 0;
	dr_spr.draw_end_x = sprite_w / 2 + dr_spr.sprite_screen_x;
	if (dr_spr.draw_end_x >= vars->width)
		dr_spr.draw_end_x = vars->width - 1;
	show_sprite(vars, dr_spr, sprite_w, p_buffer);
}

void	sprite_raycast(t_vars *vars, double p_buffer[vars->width])
{
	int				sprite_order[vars->num_sprites];
	double			sprite_distance[vars->num_sprites];
	t_draw_sprite	dr_spr;

	for(int i = 0; i < vars->num_sprites; i++)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((vars->hero.pos_x - vars->sprites[i].x) * (vars->hero.pos_x - vars->sprites[i].x) + (vars->hero.pos_y - vars->sprites[i].y) * (vars->hero.pos_y - vars->sprites[i].y)); //sqrt not taken, unneeded
	}
 	sort_sprites(sprite_order, sprite_distance, vars->num_sprites);
	for(int i = 0; i < vars->num_sprites; i++)
	{
		//translate sprite position to relative to camera
		double sprite_x = vars->sprites[sprite_order[i]].x - vars->hero.pos_x;
		double sprite_y = vars->sprites[sprite_order[i]].y - vars->hero.pos_y;

		double inv_det = 1.0 / (vars->hero.plane_x * vars->hero.dir_y - vars->hero.dir_x * vars->hero.plane_y); //required for correct matrix multiplication

		double transform_x = inv_det * (vars->hero.dir_y * sprite_x - vars->hero.dir_x * sprite_y);
		dr_spr.transform_y = inv_det * (-vars->hero.plane_y * sprite_x + vars->hero.plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D

		dr_spr.sprite_screen_x = (int)((vars->width / 2) * (1 + transform_x / dr_spr.transform_y));

		//calculate height of the sprite on screen
		dr_spr.sprite_h = abs((int)(vars->height / (dr_spr.transform_y))); //using 'dr_spr.transform_y' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current x
		dr_spr.draw_start_y = -dr_spr.sprite_h / 2 + vars->height / 2;
		if(dr_spr.draw_start_y < 0)
			dr_spr.draw_start_y = 0;
		dr_spr.draw_end_y = dr_spr.sprite_h / 2 + vars->height / 2;
		if(dr_spr.draw_end_y >= vars->height)
			dr_spr.draw_end_y = vars->height - 1;
		draw_sprite(vars, dr_spr, p_buffer);
	}
}

void	start_and_end_init(t_vars *vars, t_draw *draws)
{
	draws->draw_start = -draws->line_h / 2 + vars->height / 2;
	if (draws->draw_start < 0)
		draws->draw_start = 0;
	draws->draw_end = draws->line_h / 2 + vars->height / 2;
	if (draws->draw_end >= vars->height)
		draws->draw_end = vars->height - 1;
}

void	raycasting(t_vars *vars, t_map *map)
{
	double	p_buffer[vars->width];
	t_draw	draws;
	int		x;
	double camera_x;

	x = 0;
	while (x < vars->width)
	{
		camera_x = 2 * x / (double)vars->width - 1;
		vars->hero.ray_dir_x = vars->hero.dir_x + vars->hero.plane_x * camera_x;
		vars->hero.ray_dir_y = vars->hero.dir_y + vars->hero.plane_y * camera_x;
		draws.map_x = (int)vars->hero.pos_x;
		draws.map_y = (int)vars->hero.pos_y;
		draws.delta_dist_x = fabs(1 / vars->hero.ray_dir_x);
		draws.delta_dist_y = fabs(1 / vars->hero.ray_dir_y);
		step_and_sidedist(vars, &draws);
		dda(vars, map, &draws);
		start_and_end_init(vars, &draws);
		draw_walls(vars, &draws, x);
		p_buffer[x] = draws.perp_wall_dist;
		++x;
	}
	sprite_raycast(vars, p_buffer);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_frame.img, 0, 0);
}
