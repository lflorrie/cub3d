#include "my_cub_utils.h"
#include "math.h"

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

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}


void	raycasting(t_vars *vars, t_map *map)
{

	double	ZBuffer[vars->width];

	for(int x = 0; x < vars->width; x++)
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
		if (perpWallDist == 0)
			perpWallDist = 0.1;
		int lineHeight = (int)(vars->height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + vars->height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + vars->height / 2;
		if(drawEnd >= vars->height) drawEnd = vars->height - 1;
		
		// texturing calculations
		// calculate value of wallX
		int texX;

		if (side == 0)
		{
			if (vars->hero.ray_dir_x < 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_n.width);
				show_line(vars, &vars->img_n, drawStart, drawEnd, x, texX, &vars->img_frame, lineHeight);
			}

			if (vars->hero.ray_dir_x > 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_s.width);
				show_line(vars, &vars->img_s, drawStart, drawEnd, x, texX, &vars->img_frame, lineHeight);
			}
		}
		if (side == 1)
		{
			if (vars->hero.ray_dir_y < 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_w.width);
				show_line(vars, &vars->img_w, drawStart, drawEnd, x, texX, &vars->img_frame, lineHeight);
			}
			if (vars->hero.ray_dir_y > 0)
			{
				texX = calc_texture(vars, perpWallDist, side, vars->img_e.width);
				show_line(vars, &vars->img_e, drawStart, drawEnd, x, texX, &vars->img_frame, lineHeight);
			}
		}
	 	ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}

	//SPRITES
	int		spriteOrder[vars->num_sprites];
	double	spriteDistance[vars->num_sprites];
	for(int i = 0; i < vars->num_sprites; i++)
	{
	  spriteOrder[i] = i;
	  spriteDistance[i] = ((vars->hero.pos_x - vars->sprites[i].x) * (vars->hero.pos_x - vars->sprites[i].x) + (vars->hero.pos_y - vars->sprites[i].y) * (vars->hero.pos_y - vars->sprites[i].y)); //sqrt not taken, unneeded
	}
 	sortSprites(spriteOrder, spriteDistance, vars->num_sprites);
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
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= vars->width) drawEndX = vars->width - 1;
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * vars->img_spr.width / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < vars->width && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - vars->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * vars->img_spr.height) / spriteHeight) / 256;
         	if (texY >= 0 && texX >= 0)
         	{
          	unsigned char *src = (unsigned char *)get_pixel(&vars->img_spr, texX, texY);
			
			unsigned char b = src[0];
			unsigned char g = src[1];
			unsigned char r = src[2];
			unsigned char t = src[3];
			if (t != 255)
				my_mlx_pixel_put(&vars->img_frame, stripe, y, create_rgb(r, g, b));
        	}
        }
    }
	}

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_frame.img, 0, 0);
}