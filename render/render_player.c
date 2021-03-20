#include "cub3d.h"

static void side_step(t_game *game, double rayDirX, double rayDirY)
{
    if(rayDirX < 0)
    {
        game->ray.stepX = -1;
        game->player.sideDistX = (game->player.posX - game->ray.mapX) * game->ray.deltaDistX;
    }
    else
    {
        game->ray.stepX = 1;
        game->player.sideDistX = (game->ray.mapX + 1.0 - game->player.posX) * game->ray.deltaDistX;
    }
    if(rayDirY < 0)
    {
        game->ray.stepY = -1;
        game->player.sideDistY = (game->player.posY - game->ray.mapY) * game->ray.deltaDistY;
    }
    else
    {
        game->ray.stepY = 1;
        game->player.sideDistY = (game->ray.mapY + 1.0 - game->player.posY) * game->ray.deltaDistY;
    }
}

static void dda_perform(t_game *game, double rayDirX, double rayDirY)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if(game->player.sideDistX < game->player.sideDistY)
        {
            game->player.sideDistX += game->ray.deltaDistX;
            game->ray.mapX += game->ray.stepX;
            game->player.side = 0;
        }
        else
        {
            game->player.sideDistY += game->ray.deltaDistY;
            game->ray.mapY += game->ray.stepY;
            game->player.side = 1;
        }
        if(game->map.map[game->ray.mapY][game->ray.mapX] == '1' || game->map.map[game->ray.mapY][game->ray.mapX] == '2'
        || game->map.map[game->ray.mapY][game->ray.mapX] == '3' || game->map.map[game->ray.mapY][game->ray.mapX] == '4' 
        || game->map.map[game->ray.mapY][game->ray.mapX] == '5')
            hit = 1;
    }
    if(game->player.side == 0)
        game->player.to_wall = (game->ray.mapX - game->player.posX + (1 - game->ray.stepX) / 2) / rayDirX;
    else
        game->player.to_wall = (game->ray.mapY - game->player.posY + (1 - game->ray.stepY) / 2) / rayDirY;
    game->ray.lineHeight = (int)(game->mlx.win_width / game->player.to_wall);
}

void print_ray(t_game *game)
{
    int x;
    double cameraX;
    double rayDirX;
    double rayDirY;

    x = 0;
    while (x < game->mlx.win_width)
    {
        cameraX = 2 * x / (double)game->mlx.win_width - 1;  
        rayDirX = game->player.dirX + game->player.planeX * cameraX;
        rayDirY = game->player.dirY + game->player.planeY * cameraX;

        game->ray.mapX = (int)(game->player.posX);
        game->ray.mapY = (int)(game->player.posY);

        game->ray.deltaDistX = fabs(1 / rayDirX);
        game->ray.deltaDistY = fabs(1 / rayDirY);

        side_step(game, rayDirX, rayDirY);
        dda_perform(game, rayDirX, rayDirY);

        game->ray.drawStart = -game->ray.lineHeight / 2 + game->mlx.win_hight / 2;
        if(game->ray.drawStart < 0)
            game->ray.drawStart = 0;
        game->ray.drawEnd = game->ray.lineHeight / 2 + game->mlx.win_hight / 2;
        if(game->ray.drawEnd >= game->mlx.win_hight)
            game->ray.drawEnd = game->mlx.win_hight - 1;
        //choose wall color
        int color = 0xFFFFFF;
        int red_color = 0xff3333;
        int green_color = 0x339933;
        int blue_color = 0x3366cc;
        int yellow_color = 0xffff55;
        if (game->map.map[game->ray.mapY][game->ray.mapX] == '1')
            color = red_color;
        if (game->map.map[game->ray.mapY][game->ray.mapX] == '2')
            color = green_color;
        if (game->map.map[game->ray.mapY][game->ray.mapX] == '3')
            color = blue_color;
        if (game->map.map[game->ray.mapY][game->ray.mapX] == '4')
            color = 0xFFFFFF; 
        if (game->map.map[game->ray.mapY][game->ray.mapX] == '5')
            color = yellow_color; 
        if (game->player.side == 1) 
            color = color / 1.5;
        
        drow_line(game->data, x, game->ray.drawStart, game->ray.drawEnd, color);
        x++;
    }
}