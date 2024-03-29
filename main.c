/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:48:21 by lflorrie          #+#    #+#             */
/*   Updated: 2021/04/02 16:48:24 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cub_utils.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		proc_w(vars);
	if (keycode == KEY_S)
		proc_s(vars);
	if (keycode == KEY_A)
		proc_a(vars);
	if (keycode == KEY_D)
		proc_d(vars);
	if (keycode == KEY_RIGHT_ARROW)
		proc_key_r_arrow(vars);
	if (keycode == KEY_LEFT_ARROW)
		proc_key_l_arrow(vars);
	if (keycode == KEY_ESC)
		proc_key_esc(vars);
	raycasting(vars, &vars->map);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_frame.img, 0, 0);
	return (0);
}

int	ft_close(t_vars *vars)
{
	proc_key_esc(vars);
	exit(0);
}

void	init_hero_and_text(t_vars *vars)
{
	vars->hero = get_hero(vars->map);
	init_sprites(vars);
	vars->img_n = init_image_from_file(vars->mlx, vars->map.pict_north);
	vars->img_s = init_image_from_file(vars->mlx, vars->map.pict_south);
	vars->img_e = init_image_from_file(vars->mlx, vars->map.pict_east);
	vars->img_w = init_image_from_file(vars->mlx, vars->map.pict_west);
	vars->img_spr = init_image_from_file(vars->mlx, vars->map.pict_sprite);
}

void	main_loop(t_vars vars, int argc)
{
	init_hero_and_text(&vars);
	if (vars.hero.speed_x == 0 || vars.hero.pos_x == 0)
		printf("Error!\nProblem with hero!\n");
	else if (argc == 2)
	{
		init_window(&vars, vars.map.width, vars.map.height);
		vars.img_frame = init_image(vars.mlx, vars.width, vars.height);
		mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
		mlx_hook(vars.win, 17, 1L << 17, ft_close, &vars);
		raycasting(&vars, &vars.map);
		mlx_put_image_to_window(vars.mlx, vars.win, vars.img_frame.img, 0, 0);
		mlx_loop(vars.mlx);
	}
	else
	{
		vars.img_frame = init_image(vars.mlx, vars.map.screen_width,
				vars.map.screen_width);
		vars.width = vars.map.screen_width;
		vars.height = vars.map.screen_height;
		raycasting(&vars, &vars.map);
		screen_shot(&vars);
		ft_free_map(&vars.map);
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;
	char	*errors;

	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
			if (ft_strncmp(argv[2], "--save", 7))
				exit(1 + 0 * printf("Error!\nWrong arguments\n"));
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
			exit(1 + 0 * printf("Error!\nFile must be .cub\n"));
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(1 + 0 * printf("Error!\nFile not exist.\n"));
		vars.mlx = mlx_init();
		errors = parser(vars.mlx, fd, &vars.map);
		close(fd);
		if (ft_strlen(errors) != 0)
			exit(1 + 0 * printf("%s", errors));
		main_loop(vars, argc);
	}
	else
		printf("Error!\nWrong arguments\n");
	return (0);
}
