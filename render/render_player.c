#include "cub3d.h"

static void            drow_line(t_data data, int current_x, int startY, int endY, int color)
{
    char    *dst;
    while (startY < endY)
    {
        dst = data.addr + (startY * data.line_length + current_x * (data.bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        startY++;
    }
}

static double print_ray_on_map(t_game *game, double start)
{
    double to_wall = 0;

    int x = game->player.posX;
    int y = game->player.posY;

    while (game->map.map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
    {
        x = game->player.posX + to_wall * cos(start);
        y = game->player.posY + to_wall * sin(start);
        to_wall += 0.1;
        my_mlx_pixel_put(game->data, x, y, 0xff0000);
    }
    return (to_wall);    
}

 void print_ray(t_game *game)
{
    double to_wall;

    double start = game->player.rotation_angle - (30 * M_PI / 180);
    int x_width = 0;
    while(x_width != screenWidth)
    {   
        to_wall = print_ray_on_map(game, start) * cos(game->player.rotation_angle - start);
        int lineHeight = (int)(screenHight / to_wall * TILE_SIZE);
        start +=(((float)60 / screenWidth) * M_PI / 180);
        int drawStart = screenHight / 2 - lineHeight / 2;

        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = screenHight / 2 + lineHeight / 2;

        if(drawEnd >= screenHight)
            drawEnd = screenHight - 1;
        drow_line(game->data,x_width, drawStart, drawEnd, 0x390039);
        x_width++;
    }
}

// void print_ray(t_game *game)
// {
//     printf("hi\n");
//     for(int current_x = 0; current_x < screenWidth; current_x++)
//     {
//       //calculate ray position and direction
//       double cameraX = 2 * current_x / (double)screenWidth - 1; //x-coordinate in camera space
//       double rayDirX = game->player.dirX + game->player.planeX * cameraX; // 0
//       double rayDirY = game->player.dirY + game->player.planeY * cameraX; // 0.66
//       //which box of the map we're in
//       int mapX = (int)(game->player.posX / TILE_SIZE);
//       int mapY = (int)(game->player.posY / TILE_SIZE);

//       //length of ray from current position to next x or y-side
//       double sideDistX;
//       double sideDistY;

//        //length of ray from one x or y-side to next x or y-side
//       double deltaDistX = fabs(1 / rayDirX);
//       double deltaDistY = fabs(1 / rayDirY);
//       double perpWallDist;

//       //what direction to step in x or y-direction (either +1 or -1)
//       int stepX;
//       int stepY;

//       int hit = 0; //was there a wall hit?
//       int side; //was a NS or a EW wall hit?
//       //calculate step and initial sideDist

//       printf("hi\n");
//       if(rayDirX < 0)
//       {
//         stepX = -1;
//         sideDistX = (game->player.posX - mapX) * deltaDistX;
//       }
//       else
//       {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
//       }
//       if(rayDirY < 0)
//       {
//         stepY = -1;
//         sideDistY = (game->player.posY - mapY) * deltaDistY;
//       }
//       else
//       {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
//       }
//       printf("hi\n");
//       //perform DDA
//       while (hit == 0)
//       {
//         //jump to next map square, OR in x-direction, OR in y-direction
//         if(sideDistX < sideDistY)
//         {
//           sideDistX += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           sideDistY += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         //Check if ray has hit a wall
//         if(game->map.map[mapY][mapX] == '1') hit = 1;
//       }
//       //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
//       if(side == 0) perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX ;
//       else          perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY ;

//       //Calculate height of line to draw on screen
//       int lineHeight = (int)(screenHight / perpWallDist) * TILE_SIZE;
//         printf("lineHeight = %d\n", lineHeight);
//       //calculate lowest and highest pixel to fill in current stripe
//       int drawStart = -lineHeight / 2 + screenHight / 2;
//       if(drawStart < 0)drawStart = 0;
//       int drawEnd = lineHeight / 2 + screenHight / 2;
//       if(drawEnd >= screenHight)drawEnd = screenHight - 1;

//       //choose wall color
//       int color = 0xFFFFFF;
//       int red_color = 0xff3333;
//       int green_color = 0x339933;
//       int blue_color = 0x3366cc;
//       int yellow_color = 0xffff55;
//       if (game->map.map[mapY][mapX] == 1)
//         color = red_color;
//       if (game->map.map[mapY][mapX] == 2)
//         color = green_color;
//       if (game->map.map[mapY][mapX] == 3)
//         color = blue_color;
//       if (game->map.map[mapY][mapX] == 4)
//         color = 0xFFFFFF; 
//       if (game->map.map[mapY][mapX] == 4)
//         color = yellow_color; 
//     //   switch(game->map.map[mapY][mapX])
//     //   {
//     //     case 1:  color = RGB_Red;    break; //red
//     //     case 2:  color = RGB_Green;  break; //green
//     //     case 3:  color = RGB_Blue;   break; //blue
//     //     case 4:  color = RGB_White;  break; //white
//     //     default: color = RGB_Yellow; break; //yellow
//     //   }

//       //give x and y sides different brightness
//       if(side == 1) {color = red_color / 2;}
//       if(side == 2) {color = green_color / 1.2;}
//       if(side == 3) {color = blue_color / 1.2;}
//       if(side == 4) {color = 0xFFFFFF / 1.2;}
//       if(side == 5) {color = yellow_color / 1.2;}

//         drow_line(game->data,current_x, drawStart, drawEnd, 0x390039);
//     }
// }

void print_player(t_game *game)
{
    float x;
    float y; 
    int R;
    double angle;

    angle = 0;
    x = game->player.posX;
    y = game->player.posY; 
    R = game->player.radius;
	while (R != 0) 
    {
        angle = 0;
		while (angle < 2 * M_PI) 
        {
			int main_x = R * cos(angle);
			int main_y = R * sin(angle);
            my_mlx_pixel_put(game->data, main_x + x, main_y + y, 0xff0000);
            angle += 0.01;
		}
		R -=0.01;
	}
}