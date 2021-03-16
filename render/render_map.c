#include "cub3d.h"

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

// static void print_back(t_game *game)
// {
// 	int x;
// 	int y;

// 	x = 0;
// 	while (x != screenWidth - 1)
// 	{
// 		y = 0;
// 		while(y != screenHight - 1)
// 		{
// 			if (y < screenHight)
// 				my_mlx_pixel_put(game->data, x, y, 0x0000ff);
// 			else
// 				my_mlx_pixel_put(game->data, x, y, 0xffff00);
// 			y++;
// 		}
// 		x++;
// 	}
// }

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
			game->map.color = *str - '0' == 1 ? 0x222222 : 0xFFFFFF;
			main_x += rect(game, main_x, main_y, *str) * TILE_SIZE;
			str++;
			tmp++;
		}
		main_y+=TILE_SIZE;
		main_x = 0;
		tmp = 0;
	}
}