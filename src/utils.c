/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:17:27 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:17:29 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	pxl(t_data *txtr, int x, int y)
{
	int		*ptr;
	int		color;

	ptr = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int *) ptr;
	return (color);
}

int	init_sprite_structure(t_game *game)
{
	int		x;
	int		y;
	int		ind;

	x = 0;
	y = 0;
	ind = 0;
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			if (game->map.map[y][x] == '2')
			{
				sprt_pos_add_back(&game->sprt_pos, sprt_pos_new(x, y, ind));
				ind++;
			}
			x++;
		}
		y++;
		x = 0;
	}
	game->tmp = game->sprt_pos;
	game->sprt_pos = game->tmp->next;
	return (0);
}

void	draw_sprite(int x, int y, t_game *game, int txt_h)
{
	while (y < game->sprs.end_y)
	{
		game->sprs.d = (y) * 256 - game->mlx.win_hight * 128 + \
		game->sprs.spr_height * 128;
		game->sprs.txtr_y = ((game->sprs.d * txt_h) / game->sprs.spr_height) \
		/ 256;
		game->sprs.color = pxl(game->txtr.sprite, game->sprs.txtr_x, \
		game->sprs.txtr_y);
		if ((game->sprs.color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(game->data, x, y, game->sprs.color);
		y++;
	}
}

int	close_programm(__unused t_game *game)
{
	mlx_destroy_image(game->mlx.mlx, game->data.img);
	mlx_clear_window(game->mlx.mlx, game->mlx.mlx_win);
	mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
	exit(0);
}
