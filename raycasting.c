
void raycasting()
{
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
		hero.ray_dir_x = hero.dir_x + hero.plane_x * cameraX;
		hero.ray_dir_y = hero.dir_y + hero.plane_y * cameraX;

		//which box of the map we're in
		int mapX = int(hero.pos_x);
		int mapY = int(hero.pos_y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = std::abs(1 / hero.ray_dir_x);
		double deltaDistY = std::abs(1 / hero.ray_dir_y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if(hero.ray_dir_x < 0)
		{
		  stepX = -1;
		  sideDistX = (hero.pos_x - mapX) * deltaDistX;
		}
		else
		{
		  stepX = 1;
		  sideDistX = (mapX + 1.0 - hero.pos_x) * deltaDistX;
		}
		if(hero.ray_dir_y < 0)
		{
		  stepY = -1;
		  sideDistY = (hero.pos_y - mapY) * deltaDistY;
		}
		else
		{
		  stepY = 1;
		  sideDistY = (mapY + 1.0 - hero.pos_y) * deltaDistY;
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
		  if(worldMap[mapX][mapY] > 0) hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - hero.pos_x + (1 - stepX) / 2) / hero.ray_dir_x;
		else          perpWallDist = (mapY - hero.pos_y + (1 - stepY) / 2) / hero.ray_dir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h) drawEnd = h - 1;
		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = hero.pos_y + perpWallDist * hero.ray_dir_y;
		else           wallX = hero.pos_x + perpWallDist * hero.ray_dir_x;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = int(wallX * double(texWidth));
		if(side == 0 && hero.ray_dir_x > 0) texX = texWidth - texX - 1;
		if(side == 1 && hero.ray_dir_y < 0) texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
		  // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		  int texY = (int)texPos & (texHeight - 1);
		  texPos += step;
		  Uint32 color = texture[texNum][texHeight * texY + texX];
		  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		  if(side == 1) color = (color >> 1) & 8355711;
		  buffer[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}
}
