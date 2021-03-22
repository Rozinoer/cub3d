#include "cub3d.h"

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

static int    rect(t_game *game, int main_x, int main_y, char c)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < TILE_SIZE)
	{
		while (x < TILE_SIZE)
		{
			if (ft_isdigit(c) || c == 'N' || c == 'W' || c == 'S' || c == 'E')
			{
				my_mlx_pixel_put(game->data, main_x + x, main_y + y, game->map.color);
				if (y == 0 || y == TILE_SIZE - 1)
				{
					if (x == 0 || x == TILE_SIZE - 1)
						my_mlx_pixel_put(game->data, main_x + x, main_y + y, 0x222222);
				}
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (1);
}

void print_map(t_game *game)
{
	int main_x = 0;
	int main_y = 0;
	int i = -1;
	int tmp = 0;
	char* str = NULL;

	// print_back(game);
	while (game->map.map[++i])
	{
		str = game->map.map[i];
		while (*str)
		{
			game->map.color = *str - '0' >= 1 ? 0x222222 : 0xFFFFFF;
			main_x += rect(game, main_x, main_y, *str) * TILE_SIZE;
			str++;
			tmp++;
		}
		main_y+=TILE_SIZE;
		main_x = 0;
		tmp = 0;
	}
}