/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:05:37 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:05:39 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"	

static void	env(t_game *game, int x, int y)
{
	if ((y == 0 || y == game->map.map_size - 1) || \
	(x == (int)ft_strlen(game->map.map[y] - 1) || x == 0))
		ft_error("Map is unclosed!\n");
	else if (game->map.map[y][x + 1] && game->map.map[y][x - 1] &&
				game->map.map[y + 1][x] && game->map.map[y - 1][x])
	{
		if (game->map.map[y][x + 1] == ' ' || game->map.map[y][x - 1] == ' '
		|| game->map.map[y + 1][x] == ' ' || game->map.map[y - 1][x] == ' ')
			ft_error("Map is unclosed!\n");
	}
	else
		ft_error("Map is unclosed!\n");
}

static void	check_env(t_game *game)
{
	int		y;
	int		x;

	x = 0;
	y = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			if (game->map.map[y][x] == '0' || game->map.map[y][x] == '2' ||
			game->map.map[y][x] == 'N' || game->map.map[y][x] == 'S' ||
			game->map.map[y][x] == 'E' || game->map.map[y][x] == 'W')
				env(game, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

static void	check_sym(t_game *game, char *sym_pull)
{
	int		flag;
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	y = 0;
	flag = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			while (sym_pull[i] != '\0')
				if (game->map.map[y][x] == sym_pull[i++])
					flag++;
			if (flag == 0)
				ft_error("Map is unvalid!\n");
			flag = 0;
			i = 0;
			x++;
		}
		x = 0;
		y++;
	}
}

static void	count_sprites(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	game->sprs.amount_sprt = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			if (game->map.map[y][x] == '2')
				game->sprs.amount_sprt++;
			x++;
		}
		x = 0;
		y++;
	}
	if (game->sprs.amount_sprt > 0)
		allocate_memory(game);
}

int	check_map(t_game *game)
{
	check_sym(game, " 012NSWE");
	check_env(game);
	count_sprites(game);
	init_sprite_structure(game);
	return (1);
}
