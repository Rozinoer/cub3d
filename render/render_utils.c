#include "cub3d.h"

int			ft_get_pxl_clr(t_data *txtr, int x, int y)
{
	int		*ptr;
	int		color;

	ptr = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int*)ptr;
	return (color);
}

void print_back(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x != game->mlx.win_width)
    {
        while (y != game->mlx.win_hight)
        {
            if (y <= game->mlx.win_hight * 0.5)
                my_mlx_pixel_put(game->data, x, y, game->map.ceiling_color);
            else
                my_mlx_pixel_put(game->data, x, y, game->map.floor_color);
            y++;    
        }
        x++;
        y = 0;
    }
}