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
			if (ft_isdigit(c))
				// mlx_pixel_put(game->mlx.mlx, game->mlx.mlx_win, main_x + x, main_y + y, game->map.color);
				my_mlx_pixel_put(game->data, main_x + x, main_y + y, game->map.color);
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
			// if (*str == 'N')
			// {
			// 	game->player.posX = tmp * TILE_SIZE;
			// 	game->player.posY = i * TILE_SIZE;
			// }
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