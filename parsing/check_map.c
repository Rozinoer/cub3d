#include "cub3d.h"	

static void check_env(t_game *game)
{
	int y;
	int x;

	x = 0;
	y = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			if (game->map.map[y][x] == '0' || game->map.map[y][x] == '2' ||
			game->map.map[y][x] == 'N' || game->map.map[y][x] == 'S' ||
			game->map.map[y][x] == 'E' || game->map.map[y][x] == 'W')
			{
				if (game->map.map[y][x + 1] == ' ' || game->map.map[y][x - 1] == ' ' 
				|| game->map.map[y + 1][x] == ' ' || game->map.map[y - 1][x] == ' ')
					ft_error("Error. Map is unclosed!\n");
			}
			x++;
		}
		x = 0;
		y++;
	}
}

static void check_sym(t_game *game, char *sym_pull)
{
	int flag;
	int x;
	int y;
	int i;

	i = 0;
	x = 0;
	y = 0;
	flag = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			while (sym_pull[i] != '\0')
				if(game->map.map[y][x] == sym_pull[i++])
					flag++;
			if (flag == 0)
				ft_error("Error. Map is unvalid!\n");
			flag = 0;
			i = 0;
			x++;
		}
		x = 0;
		y++;
	}
}

int check_map(t_game *game)
{
	check_sym(game, " 012NSWE");
	check_env(game);

	return (1);
}