
/* ************************************************************************** */

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
				if(game->map.map[y][x + 1] && game->map.map[y][x - 1] 
					&& game->map.map[y + 1][x] && game->map.map[y - 1][x])
				{
					if (game->map.map[y][x + 1] == ' ' || game->map.map[y][x - 1] == ' ' 
					|| game->map.map[y + 1][x] == ' ' || game->map.map[y - 1][x] == ' ')
						ft_error("Error. Map is unclosed!\n");
				}
				else
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

static void allocate_memory(t_game *game)
{
	game->sprt_pos = malloc(sizeof(t_sprt_pos));
	if(!(game->sprt_pos))
		ft_error("Error memory allocation\n");
	game->spr_dist = malloc(game->sprites.amount_sprt * sizeof(double));
	if (!(game->spr_dist))
		ft_error("Error memory allocation\n");
	game->spr_oder = malloc(game->sprites.amount_sprt * sizeof(int));
	if (!(game->spr_oder))
		ft_error("Error memory allocation\n");
	game->z_buff = malloc(game->mlx.win_width * sizeof(double));
	if (!(game->z_buff))
		ft_error("Error memory allocation\n");
}

static void count_sprites(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	game->sprites.amount_sprt = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			if(game->map.map[y][x] == '2')
				game->sprites.amount_sprt++;
			x++;
		}
		x = 0;
		y++;
	}
	allocate_memory(game);
}

int check_map(t_game *game)
{
	check_sym(game, " 012NSWE");
	check_env(game);
	count_sprites(game);
	init_sprite_structure(game);
	return (1);
}