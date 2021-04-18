#include "my_cub_utils.h"
#include "math.h"

void	start_and_end_init(t_vars *vars, t_draw *draws, t_map *map)
{
	step_and_sidedist(vars, draws);
	dda(vars, map, draws);
	draws->draw_start = -draws->line_h / 2 + vars->height / 2;
	if (draws->draw_start < 0)
		draws->draw_start = 0;
	draws->draw_end = draws->line_h / 2 + vars->height / 2;
	if (draws->draw_end >= vars->height)
		draws->draw_end = vars->height - 1;
}

void	raycasting(t_vars *vars, t_map *map)
{
	double	*p_buffer;
	t_draw	draws;
	int		x;
	double	camera_x;

	x = 0;
	p_buffer = (double *)malloc(sizeof(double) * vars->width);
	if (!p_buffer)
		return ;
	while (x < vars->width)
	{
		camera_x = 2 * x / (double)vars->width - 1;
		vars->hero.ray_dir_x = vars->hero.dir_x + vars->hero.plane_x * camera_x;
		vars->hero.ray_dir_y = vars->hero.dir_y + vars->hero.plane_y * camera_x;
		draws.map_x = (int)vars->hero.pos_x;
		draws.map_y = (int)vars->hero.pos_y;
		draws.delta_dist_x = fabs(1 / vars->hero.ray_dir_x);
		draws.delta_dist_y = fabs(1 / vars->hero.ray_dir_y);
		start_and_end_init(vars, &draws, map);
		draw_walls(vars, &draws, x);
		p_buffer[x++] = draws.perp_wall_dist;
	}
	sprite_raycast(vars, p_buffer);
	screen_shot(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_frame.img, 0, 0);
	free(p_buffer);
}
