#include "mlx.h"
#include "my_cub_utils.h"

void init_window(t_vars *vars, int w, int h)
{
	vars->mlx = mlx_init();
	vars->width = w;
	vars->height = h;
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "Cub3d_lflorrie");
}

int		main(int argc, char **argv)
{
	t_vars	vars;

	init_window(&vars, 800, 600);
	write(1, "OK\n", 3);
	mlx_loop(vars.mlx);
	write(1, "OK\n", 3);
	return (0);
}