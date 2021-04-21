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

void	ft_draw_spr(t_game *game, int txt_w, int txt_h)
{
	int				x;
	int				y;

	x = game->sprs.draw_start_x;
	while (x < game->sprs.draw_end_x)
	{
		game->sprs.txtr_x = (int)(256 * (x - (-game->sprs.sprite_width / 2 + \
					game->sprs.spr_x)) * txt_w / game->sprs.sprite_width) / 256;
		if (game->sprs.transf_y > 0 && x > 0 && x < game->mlx.win_width && \
				game->sprs.transf_y < game->z_buff[x])
		{
			y = game->sprs.start_y;
			draw_sprite(x, y, game, txt_h);
		}
		x++;
	}
}

static void	spr_utils(t_game *game)
{
	if (game->sprs.start_y < 0)
		game->sprs.start_y = 0;
	game->sprs.end_y = game->sprs.spr_height / 2 + game->mlx.win_hight / 2;
	if (game->sprs.end_y >= game->mlx.win_hight)
		game->sprs.end_y = game->mlx.win_hight - 1;
	game->sprs.sprite_width = abs((int)(game->mlx.win_hight / \
	(game->sprs.transf_y)));
	game->sprs.draw_start_x = game->sprs.spr_x - game->sprs.sprite_width / 2;
	if (game->sprs.draw_start_x < 0)
		game->sprs.draw_start_x = 0;
	game->sprs.draw_end_x = game->sprs.sprite_width / 2 + game->sprs.spr_x;
	if (game->sprs.draw_end_x >= game->mlx.win_width)
		game->sprs.draw_end_x = game->mlx.win_width - 1;
}

void	spr(t_sprt_pos *sprite, t_player player, t_game *game)
{	
	game->sprs.x = (double)sprite->x + 0.5 - player.pos_x;
	game->sprs.y = (double)sprite->y + 0.5 - player.pos_y;
	game->sprs.inv_det = 1.0 / (player.plane_x * player.dir_y \
	- player.dir_x * player.plane_y);
	game->sprs.transf_x = game->sprs.inv_det * \
	(player.dir_y * game->sprs.x - player.dir_x * game->sprs.y);
	game->sprs.transf_y = game->sprs.inv_det * \
	(-player.plane_y * game->sprs.x + player.plane_x * game->sprs.y);
	game->sprs.spr_x = (long long int)((game->mlx.win_width / 2) * \
							(1 + game->sprs.transf_x / game->sprs.transf_y));
	game->sprs.spr_height = llabs((long long int)(game->mlx.win_hight / \
	(game->sprs.transf_y)));
	game->sprs.start_y = -game->sprs.spr_height / 2 + game->mlx.win_hight / 2;
	spr_utils(game);
}

int	init_sprite(t_game *game)
{
	int				i;
	int				j;
	double			spr_x;
	double			spr_y;

	i = 0;
	while (i < game->sprs.amount_sprt)
	{
		spr_x = (double)get_sprite(game, i)->x + 0.5;
		spr_y = (double)get_sprite(game, i)->y + 0.5;
		game->spr_dist[i] = (pow((game->player.pos_x - spr_x), 2) + \
								pow((game->player.pos_y - spr_y), 2));
		i++;
	}
	i = 0;
	j = 0;
	ft_sort(game, i, j);
	return (0);
}

void	render_sprite(t_game *game)
{
	game->tmp = game->sprt_pos;
	if (game->sprs.amount_sprt > 0)
	{
		init_sprite(game);
		while (game->sprt_pos->next != NULL)
		{
			spr(game->sprt_pos, game->player, game);
			if (game->sprs.draw_start_x < game->sprs.draw_end_x)
				ft_draw_spr(game, game->txtr.sprite->width, \
				game->txtr.sprite->height);
			game->sprt_pos = game->sprt_pos->next;
		}
		spr(game->sprt_pos, game->player, game);
		if (game->sprs.draw_start_x < game->sprs.draw_end_x)
			ft_draw_spr(game, game->txtr.sprite->width, \
			game->txtr.sprite->height);
		game->sprt_pos = game->tmp;
	}
}
