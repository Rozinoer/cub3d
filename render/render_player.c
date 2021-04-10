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

static void choose_textr(t_game *game)
{
    if (game->player.side == 1 && game->ray.stepY < 0)
		game->txtr.current = game->txtr.wall_n;
	else if (game->player.side == 1 && game->ray.stepY > 0)
        game->txtr.current = game->txtr.wall_s;
	else if (game->player.side == 0 && game->ray.stepX < 0)
        game->txtr.current = game->txtr.wall_e;
	else if (game->player.side == 0 && game->ray.stepX > 0)
        game->txtr.current = game->txtr.wall_w;
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
        if(game->map.map[game->ray.mapY][game->ray.mapX] == '1')
            hit = 1;
    }
    if(game->player.side == 0)
        game->player.to_wall = (game->ray.mapX - game->player.posX + (1 - game->ray.stepX) / 2) / rayDirX;
    else
        game->player.to_wall = (game->ray.mapY - game->player.posY + (1 - game->ray.stepY) / 2) / rayDirY;
    game->ray.lineHeight = (int)(game->mlx.win_width / game->player.to_wall);
    choose_textr(game);
}

static void calculate_txtr_pos(t_game *game, int x)
{
    game->ray.drawStart = -game->ray.lineHeight / 2 + game->mlx.win_hight / 2;
    if(game->ray.drawStart < 0)
        game->ray.drawStart = 0;
    game->ray.drawEnd = game->ray.lineHeight / 2 + game->mlx.win_hight / 2;
    if(game->ray.drawEnd >= game->mlx.win_hight)
        game->ray.drawEnd = game->mlx.win_hight - 1;
    if (game->player.side == 0)
        game->txtr.wallX = game->player.posY + game->player.to_wall * game->player.dirY;
    else
        game->txtr.wallX = game->player.posX + game->player.to_wall * game->player.dirX;
    game->txtr.wallX -= floor(game->txtr.wallX);
    game->txtr.texX = (int)(game->txtr.wallX * (double)texWidth);
    game->txtr.step = 1.0 * texHeight / game->ray.lineHeight;
    game->txtr.texPos = (game->ray.drawStart - game->mlx.win_hight / 2.0 + \
        game->ray.lineHeight / 2.0) * game->txtr.step;
    while(game->ray.drawStart < game->ray.drawEnd)
    {
        game->txtr.texY = (int)game->txtr.texPos & (texHeight - 1);
        game->txtr.texPos += game->txtr.step;

        int color = ft_get_pxl_clr(game->txtr.current, game->txtr.texX, game->txtr.texY);
        my_mlx_pixel_put(game->data, x, game->ray.drawStart, color);
        game->ray.drawStart++;
    }
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
        calculate_txtr_pos(game, x);
        x++;
    }
}