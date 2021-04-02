#include "my_cub_utils.h"
#include "math.h"

// #define texWidth 64 // must be power of two
// #define texHeight 64 // must be power of two
// unsigned buffer[600][800]; // y-coordinate first because it works per scanline

// //1D Zbuffer
// double ZBuffer[800];

int		calc_texture(t_vars *vars, double perpWallDist, int side, int img_width)
{
	double wallX; //where exactly the wall was hit
	
	if (side == 0) wallX = vars->hero.pos_y + perpWallDist * vars->hero.ray_dir_y;
	else           wallX = vars->hero.pos_x + perpWallDist * vars->hero.ray_dir_x;
	
	wallX -= floor((wallX));
	//x coordinate on the texture
	int texX = (int)(wallX * (double)img_width);
	if(side == 0 && vars->hero.ray_dir_x > 0) texX = img_width - texX - 1;
	if(side == 1 && vars->hero.ray_dir_y < 0) texX = img_width - texX - 1;
	return (texX);
}

void	raycasting(t_vars *vars, t_map *map)
{
	for(int x = 0; x <= vars->width; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)vars->width - 1; //x-coordinate in camera space
		vars->hero.ray_dir_x = vars->hero.dir_x + vars->hero.plane_x * cameraX;
		vars->hero.ray_dir_y = vars->hero.dir_y + vars->hero.plane_y * cameraX;

		//which box of the map we're in
		int mapX = (int)vars->hero.pos_x;
		int mapY = (int)vars->hero.pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / vars->hero.ray_dir_x);
		double deltaDistY = fabs(1 / vars->hero.ray_dir_y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if(vars->hero.ray_dir_x < 0)
		{
		  stepX = -1;
		  sideDistX = (vars->hero.pos_x - mapX) * deltaDistX;
		}
		else
		{
		  stepX = 1;
		  sideDistX = (mapX + 1.0 - vars->hero.pos_x) * deltaDistX;
		}
		if(vars->hero.ray_dir_y < 0)
		{
		  stepY = -1;
		  sideDistY = (vars->hero.pos_y - mapY) * deltaDistY;
		}
		else
		{
		  stepY = 1;
		  sideDistY = (mapY + 1.0 - vars->hero.pos_y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
		  //jump to next map square, OR in x-direction, OR in y-direction
		  if(sideDistX < sideDistY)
		  {
		    sideDistX += deltaDistX;
		    mapX += stepX;
		    side = 0;
		  }
		  else
		  {
		    sideDistY += deltaDistY;
		    mapY += stepY;
		    side = 1;
		  }
		  //Check if ray has hit a wall
		  if((map->map[mapX][mapY]) == '1')
		  {
		  	hit = 1;
		  }
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - vars->hero.pos_x + (1 - stepX) / 2) / vars->hero.ray_dir_x;
		else          perpWallDist = (mapY - vars->hero.pos_y + (1 - stepY) / 2) / vars->hero.ray_dir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(vars->height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + vars->height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + vars->height / 2;
		if(drawEnd >= vars->height) drawEnd = vars->height - 1;
		
		//texturing calculations
		//calculate value of wallX
		int texX;

		if (side == 0)
		{
			if (vars->hero.ray_dir_x <= 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_n.width);
				show_line(vars, &vars->img_n, drawStart, drawEnd, x, texX, &vars->img_frame);
			}
			if (vars->hero.ray_dir_x >= 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_s.width);
				show_line(vars, &vars->img_s, drawStart, drawEnd, x, texX, &vars->img_frame);
			}
		}
		if (side == 1)
		{
			if (vars->hero.ray_dir_y <= 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_w.width);
				show_line(vars, &vars->img_w, drawStart, drawEnd, x, texX, &vars->img_frame);
			}
			if (vars->hero.ray_dir_y >= 0)
			{
		 		texX = calc_texture(vars, perpWallDist, side, vars->img_e.width);
		 		show_line(vars, &vars->img_e, drawStart, drawEnd, x, texX, &vars->img_frame);
			}
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_frame.img, 0, 0);
}
