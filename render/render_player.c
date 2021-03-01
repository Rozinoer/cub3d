#include "cub3d.h"
// # define MAX_DEPTH 16
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

 void print_ray(t_game *game)
{
    double to_wall;

    double start = game->player.rotation_angle - (30 * M_PI / 180);
    double end = game->player.rotation_angle + (30 * M_PI / 180);
    double x;
    double y;
    int x_width = 0;
    while(start <= end)
    {   
        to_wall = 0;
        x = game->player.posX;
        y = game->player.posY;
        while (game->map.map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
        {
            x += cos(start);
            y += sin(start);
            to_wall += 1;
            my_mlx_pixel_put(game->data, x, y, 0xff0000);
        }
        printf("%f\n", to_wall);        
        start +=(((float)60 / screenWidth) * M_PI / 180);
        // to_wall *= cos(game->player.rotation_angle - start);
        int lineHeight = (int)(screenHight / (to_wall / TILE_SIZE));

        int drawStart = -lineHeight / 2 + screenHight / 2;

        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHight / 2;

        if(drawEnd >= screenHight)
            drawEnd = screenHight - 1;
        drow_line(game->data,x_width, drawStart, drawEnd, 0x390039);
        x_width++;
    }
}

void print_back(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x != screenWidth)
    {
        while (y != screenHight)
        {
            if (y <= screenHight * 0.5)
                my_mlx_pixel_put(game->data, x, y, 0x00C4FF);
            else
                my_mlx_pixel_put(game->data, x, y, 0xB3FF00);
            y++;    
        }
        x++;
        y = 0;
    }
    
}

void print_player(t_game *game)
{
    float x = game->player.posX;
    float y = game->player.posY; 
    int R = game->player.radius;

	while (R != 0) {
		for (double angle = 0; angle < 2 * M_PI; angle += 0.01) {
			int main_x = R * cos(angle);
			int main_y = R * sin(angle);
            my_mlx_pixel_put(game->data, main_x + x, main_y + y, 0xff0000);
		}
		R -=0.01;
	}
}