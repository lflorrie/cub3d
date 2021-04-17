#include "my_cub_utils.h"
#include "math.h"

int		calc_texture(t_vars *vars, t_draw *draws, int img_width)
{
	double	wallX;
	int		texX;

	if (draws->side == 0)
		wallX = vars->hero.pos_y + draws->perpWallDist * vars->hero.ray_dir_y;
	else
		wallX = vars->hero.pos_x + draws->perpWallDist * vars->hero.ray_dir_x;
	wallX -= floor((wallX));
	texX = (int)(wallX * (double)img_width);
	if(draws->side == 0 && vars->hero.ray_dir_x > 0)
		texX = img_width - texX - 1;
	if(draws->side == 1 && vars->hero.ray_dir_y < 0)
		texX = img_width - texX - 1;
	return (texX);
}

void	step_and_sidedist(t_vars *vars, t_draw *draws)
{
	if (vars->hero.ray_dir_x < 0)
	{
		draws->stepX = -1;
		draws->sideDistX = (vars->hero.pos_x
			- draws->mapX) * draws->deltaDistX;
	}
	else
	{
		draws->stepX = 1;
		draws->sideDistX = (draws->mapX + 1.0
			- vars->hero.pos_x) * draws->deltaDistX;
	}
	if(vars->hero.ray_dir_y < 0)
	{
		draws->stepY = -1;
		draws->sideDistY = (vars->hero.pos_y
			- draws->mapY) * draws->deltaDistY;
	}
	else
	{
		draws->stepY = 1;
		draws->sideDistY = (draws->mapY + 1.0
			- vars->hero.pos_y) * draws->deltaDistY;
	}
}

void	dda(t_vars *vars, t_map *map, t_draw *draws)
{
	while ((map->map[draws->mapX][draws->mapY]) != '1')
	{
	  if(draws->sideDistX < draws->sideDistY)
	  {
		draws->sideDistX += draws->deltaDistX;
		draws->mapX += draws->stepX;
		draws->side = 0;
	  }
	  else
	  {
		draws->sideDistY += draws->deltaDistY;
		draws->mapY += draws->stepY;
		draws->side = 1;
	  }
	}
	if(draws->side == 0)
		draws->perpWallDist = (draws->mapX - vars->hero.pos_x
			+ (1 - draws->stepX) / 2) / vars->hero.ray_dir_x;
	else
		draws->perpWallDist = (draws->mapY - vars->hero.pos_y 
			+ (1 - draws->stepY) / 2) / vars->hero.ray_dir_y;
	if (draws->perpWallDist == 0)
		draws->perpWallDist = 0.1;
	draws->lineHeight = (int)(vars->height / draws->perpWallDist);
}

void	draw_walls(t_vars *vars, t_draw *draws, int x)
{
	if (vars->hero.ray_dir_x < 0 && draws->side == 0)
	{
		draws->texX = calc_texture(vars, draws, vars->img_n.width);
		show_line(vars, &vars->img_n, *draws, x);
	}
	if (vars->hero.ray_dir_x > 0 && draws->side == 0)
	{
		draws->texX = calc_texture(vars, draws, vars->img_s.width);
		show_line(vars, &vars->img_s, *draws, x);
	}
	if (vars->hero.ray_dir_y < 0 && draws->side == 1)
	{
		draws->texX = calc_texture(vars, draws, vars->img_w.width);
		show_line(vars, &vars->img_w, *draws, x);
	}
	if (vars->hero.ray_dir_y > 0 && draws->side == 1)
	{
		draws->texX = calc_texture(vars, draws, vars->img_e.width);
		show_line(vars, &vars->img_e, *draws, x);
	}
}

void	raycasting(t_vars *vars, t_map *map)
{

	double	ZBuffer[vars->width];
	t_draw	draws;
	int		x;

	x = 0;
	while (x < vars->width)
	{   
		//calculate ray position and direction
		double cameraX = 2 * x / (double)vars->width - 1; //x-coordinate in camera space
		vars->hero.ray_dir_x = vars->hero.dir_x + vars->hero.plane_x * cameraX;
		vars->hero.ray_dir_y = vars->hero.dir_y + vars->hero.plane_y * cameraX;
		draws.mapX = (int)vars->hero.pos_x;
		draws.mapY = (int)vars->hero.pos_y;
		//length of ray from one x or y-draws.side to next x or y-draws.side
		draws.deltaDistX = fabs(1 / vars->hero.ray_dir_x);
		draws.deltaDistY = fabs(1 / vars->hero.ray_dir_y);
		//calculate step and initial sideDist
		step_and_sidedist(vars, &draws);
		//perform DDA
		dda(vars, map, &draws);
		//calculate lowest and highest pixel to fill in current stripe
		draws.drawStart = -draws.lineHeight / 2 + vars->height / 2;
		if (draws.drawStart < 0)
			draws.drawStart = 0;
		draws.drawEnd = draws.lineHeight / 2 + vars->height / 2;
		if (draws.drawEnd >= vars->height)
			draws.drawEnd = vars->height - 1;
		// texturing calculations
		// calculate value of wallX
		draw_walls(vars, &draws, x);
 		ZBuffer[x] = draws.perpWallDist;
	 	++x;
	}

	//SPRITES
	int		spriteOrder[vars->num_sprites];
	double	spriteDistance[vars->num_sprites];
	for(int i = 0; i < vars->num_sprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((vars->hero.pos_x - vars->sprites[i].x) * (vars->hero.pos_x - vars->sprites[i].x) + (vars->hero.pos_y - vars->sprites[i].y) * (vars->hero.pos_y - vars->sprites[i].y)); //sqrt not taken, unneeded
	}
 	sort_sprites(spriteOrder, spriteDistance, vars->num_sprites);
    for(int i = 0; i < vars->num_sprites; i++)
    {
      //translate sprite position to relative to camera
		double spriteX = vars->sprites[spriteOrder[i]].x - vars->hero.pos_x;
		double spriteY = vars->sprites[spriteOrder[i]].y - vars->hero.pos_y;

		double invDet = 1.0 / (vars->hero.plane_x * vars->hero.dir_y - vars->hero.dir_x * vars->hero.plane_y); //required for correct matrix multiplication

		double transformX = invDet * (vars->hero.dir_y * spriteX - vars->hero.dir_x * spriteY);
		double transformY = invDet * (-vars->hero.plane_y * spriteX + vars->hero.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((vars->width / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(vars->height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + vars->height / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + vars->height / 2;
		if(drawEndY >= vars->height) drawEndY = vars->height - 1;

		int spriteWidth = abs((int)(vars->height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= vars->width) drawEndX = vars->width - 1;
     	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
     	{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * vars->img_spr.width / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < vars->width && transformY < ZBuffer[stripe])
			for (int y = drawStartY; y < drawEndY; y++)
			{
			  int d = (y) * 256 - vars->height * 128 + spriteHeight * 128;
			  int texY = ((d * vars->img_spr.height) / spriteHeight) / 256;
			 	if (texY >= 0 && texX >= 0)
			 	{
			  	unsigned char *src = (unsigned char *)get_pixel(&vars->img_spr, texX, texY);
				if (src[3] != 255)
					my_mlx_pixel_put(&vars->img_frame, stripe, y, create_rgb(src[2], src[1], src[0]));
				}
			}
    	}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_frame.img, 0, 0);
}