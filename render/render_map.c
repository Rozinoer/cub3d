/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:16:21 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:16:24 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				my_mlx_pixel_put(game->data, main_x + x, main_y + y, game->map.color);
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
