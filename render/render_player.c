#include "cub3d.h"

static void print_wall(t_game *game, int to_wall, int flag)
{
    int static wallX = 0;
    int wallY;
    int currentY;
    int wall_hight;
    int semi_wall_hight;

    wall_hight = (float)((to_wall * 700) / 277);
    semi_wall_hight = wall_hight / 2;
    wallY = 1080 / 2;
    // printf("Высота стены: %d\nПоловина высоты стены : %d\n", wall_hight, semi_wall_hight);
    // sleep(1000);
    while (wallX % 6 != 0 && wallX <= 1920)
    {
        currentY = wallY - semi_wall_hight;
        while (currentY != wallY + semi_wall_hight)
        {
            my_mlx_pixel_put(game->data, wallX, currentY, 0xffddbb);
            currentY++;
        }
        wallX++;
    }
    wallX++;
    if (flag == 320 || flag == 321)
        wallX = 0;
}

 void print_ray(t_game *game)
{
    double start = game->player.rotation_angle - (30 * M_PI / 180);
    double end = game->player.rotation_angle + (30 * M_PI / 180);
    double x;
    double y;
    int to_wall;
    int flag = 0;
        //960 540
    int i = 0;
    while(start <= end)
    {
        x = game->player.posX;
        y = game->player.posY;
        while (game->map.map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
        {
            x += cos(start);
            y += sin(start);
            my_mlx_pixel_put(game->data, x, y, 0xff0000);
        }
        start +=(((float)60 / 320) * M_PI / 180);
        printf("angle = %f\n x = %f\ny = %f\n posX = %f\n posY = %f\n",start * 180 / M_PI,x,y,game->player.posX,game->player.posY);
        to_wall = (int)sqrt(pow(x - game->player.posX, 2) + pow(y - game->player.posY, 2));
        flag++;
        print_wall(game, to_wall, flag);
        i++;
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