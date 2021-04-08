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
        if(game->map.map[game->ray.mapY][game->ray.mapX] == '1' || game->map.map[game->ray.mapY][game->ray.mapX] == '2')
            hit = 1;
    }
    if(game->player.side == 0)
        game->player.to_wall = (game->ray.mapX - game->player.posX + (1 - game->ray.stepX) / 2) / rayDirX;
    else
        game->player.to_wall = (game->ray.mapY - game->player.posY + (1 - game->ray.stepY) / 2) / rayDirY;
    game->ray.lineHeight = (int)(game->mlx.win_width / game->player.to_wall);
}

t_data		*ft_create_img_txtr(char *file, void *ptr_mlx)
{
	t_data	*txtr;

	if (!(txtr = malloc(sizeof(t_data))))
		ft_error("Error memory allocation\n");
	txtr->img = mlx_xpm_file_to_image(ptr_mlx, file, \
							&txtr->width, &txtr->height);
	if (!txtr->img)
		ft_error("Error map: error texture\n");
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bits_per_pixel, \
							&txtr->line_length, &txtr->endian);
	return (txtr);
}

void		ft_paint_texture(t_game *game)
{
	game->txtr.wall_n = ft_create_img_txtr(game->map.no_tex, game->mlx.mlx);
	game->txtr.wall_s = ft_create_img_txtr(game->map.so_tex, game->mlx.mlx);
	game->txtr.wall_e = ft_create_img_txtr(game->map.ea_tex, game->mlx.mlx);
	game->txtr.wall_w = ft_create_img_txtr(game->map.we_tex, game->mlx.mlx);
}

int			ft_get_pxl_clr(t_data *txtr, int x, int y)
{
	int		*ptr;
	int		color;

	ptr = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int*)ptr;
	return (color);
}

void print_ray(t_game *game)
{
    int x;
    double cameraX;
    double rayDirX;
    double rayDirY;
    ft_paint_texture(game);
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
////////////////
        // int texNum = game->map.map[game->ray.mapY][game->ray.mapX] - 48;
        double wallX;
        if (game->player.side == 0)
            wallX = game->player.posY + game->player.to_wall * game->player.dirY;
        else
            wallX = game->player.posX + game->player.to_wall * game->player.dirX;
        wallX -= floor(wallX);
        int texX = (int)(wallX * (double)texWidth);
        double step = 1.0 * texHeight / game->ray.lineHeight;
        // Starting texture coordinate
        double texPos = (game->ray.drawStart - game->mlx.win_hight / 2 + game->ray.lineHeight / 2) * step;
        for (int y = game->ray.drawStart; y < game->ray.drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            int color = ft_get_pxl_clr(game->txtr.wall_n, texX, texY);
		    if ((color & 0x00FFFFFF) == 0)
			    color = 0x00111111;
            my_mlx_pixel_put(game->data, x, y, color);
        }
        x++;
    }
}