/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:16:37 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:16:39 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				ft_draw_spr(t_game *game, int txt_w, int txt_h)
{
	int				x;
	int				y;

	x = game->sprites.draw_start_x;
	while (x < game->sprites.draw_end_x)
	{
		game->sprites.txtr_x = (int)(256 * (x - (-game->sprites.sprite_width / 2 + \
					game->sprites.sprite_screen_x)) * txt_w / game->sprites.sprite_width) / 256;
		if (game->sprites.transform_y > 0 && x > 0 && x < game->mlx.win_width && \
				game->sprites.transform_y < game->z_buff[x])
		{
			y = game->sprites.draw_start_y;
			while (y < game->sprites.draw_end_y)
			{
				game->sprites.d = (y) * 256 - game->mlx.win_hight * 128 + game->sprites.sprite_height * 128;
				game->sprites.txtr_y = ((game->sprites.d * txt_h) / game->sprites.sprite_height) / 256;
				game->sprites.color = ft_get_pxl_clr(game->txtr.sprite, game->sprites.txtr_x, \
																game->sprites.txtr_y);
				if ((game->sprites.color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(game->data, x, y, game->sprites.color);
				y++;
			}
		}
		x++;
	}
}

void				spr(t_sprt_pos *sprite, t_player player, t_game *game)
{	
	game->sprites.x = (double)sprite->x + 0.5 - player.pos_x;
	game->sprites.y = (double)sprite->y + 0.5 - player.pos_y;
	game->sprites.inv_det = 1.0 / (player.plane_x * player.dir_y - player.dir_x * player.plane_y);
	game->sprites.transform_x = game->sprites.inv_det * (player.dir_y * game->sprites.x - \
										player.dir_x * game->sprites.y);
	game->sprites.transform_y = game->sprites.inv_det * (-player.plane_y * game->sprites.x + \
														player.plane_x * game->sprites.y);
	game->sprites.sprite_screen_x = (int)((game->mlx.win_width / 2) * \
							(1 + game->sprites.transform_x / game->sprites.transform_y));
	game->sprites.sprite_height = abs((int)(game->mlx.win_hight / (game->sprites.transform_y)));
	game->sprites.draw_start_y = -game->sprites.sprite_height / 2 + game->mlx.win_hight / 2;
	if (game->sprites.draw_start_y < 0)
		game->sprites.draw_start_y = 0;
	game->sprites.draw_end_y = game->sprites.sprite_height / 2 + game->mlx.win_hight / 2;
	if (game->sprites.draw_end_y >= game->mlx.win_hight)
		game->sprites.draw_end_y = game->mlx.win_hight - 1;
	game->sprites.sprite_width = abs((int)(game->mlx.win_hight / (game->sprites.transform_y)));
	game->sprites.draw_start_x = game->sprites.sprite_screen_x - game->sprites.sprite_width / 2;
	if (game->sprites.draw_start_x < 0)
		game->sprites.draw_start_x = 0;
	game->sprites.draw_end_x = game->sprites.sprite_width / 2 + game->sprites.sprite_screen_x;
	if (game->sprites.draw_end_x >= game->mlx.win_width)
		game->sprites.draw_end_x = game->mlx.win_width - 1;
}

int init_sprite_structure(t_game *game)
{
    int	x;
	int	y;
	int				ind;

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

int init_sprite(t_game *game)
{
	int				i;
	double			spr_x;
	double			spr_y;

	i = 0;
	while (i < game->sprites.amount_sprt)
	{
		spr_x = (double)get_sprite(game, i)->x + 0.5;
		spr_y = (double)get_sprite(game, i)->y + 0.5;
		game->spr_dist[i] = (pow((game->player.pos_x - spr_x), 2) + \
								pow((game->player.pos_y - spr_y), 2));
		i++;
	}
	ft_sort(game);
	return (0);
}

void render_sprite(t_game *game)
{
	game->tmp = game->sprt_pos;
	if (game->sprites.amount_sprt > 0)
	{
		init_sprite(game);
		while (game->sprt_pos->next != NULL)
		{
			spr(game->sprt_pos, game->player, game);
			if (game->sprites.draw_start_x < game->sprites.draw_end_x)
				ft_draw_spr(game, game->txtr.sprite->width, game->txtr.sprite->height);
			game->sprt_pos = game->sprt_pos->next;
		}
		spr(game->sprt_pos, game->player, game);
		if (game->sprites.draw_start_x < game->sprites.draw_end_x)
			ft_draw_spr(game, game->txtr.sprite->width, game->txtr.sprite->height);
		game->sprt_pos = game->tmp;
	}
}