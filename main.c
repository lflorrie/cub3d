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
	return (0);
}

int	ft_close(t_vars *vars)
{
	// DESTROY VSE BLIN!
	exit(0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_vars	vars;
	char	*errors;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			printf("Error!\nFile not exist.\n");
			exit(1);
		}
		vars.mlx = mlx_init();
		errors = parser(vars.mlx, fd, &vars.map);
		close(fd);
		if (ft_strlen(errors) != 0)
		{
			printf("%s", errors);
			return (1);
		}
		vars.hero = get_hero(vars.map);
		init_sprites(&vars);
		init_window(&vars, vars.map.width, vars.map.height);
		vars.img_frame = init_image(vars.mlx, vars.width, vars.height);
		vars.img_n = init_image_from_file(vars.mlx, vars.map.pict_north);
		vars.img_s = init_image_from_file(vars.mlx, vars.map.pict_south);
		vars.img_e = init_image_from_file(vars.mlx, vars.map.pict_east);
		vars.img_w = init_image_from_file(vars.mlx, vars.map.pict_west);
		vars.img_spr = init_image_from_file(vars.mlx, vars.map.pict_sprite);
		mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
		mlx_hook(vars.win, 17, 1L << 17, ft_close, &vars);
		raycasting(&vars, &vars.map);
		mlx_loop(vars.mlx);
		mlx_destroy_image(vars.mlx, &vars.img_frame);
		ft_free_map(&vars.map);
	}
	return (0);
}
