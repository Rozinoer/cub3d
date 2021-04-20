/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:16:28 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:16:30 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void side_step(t_game *game, double raydir_x, double raydir_y)
{
	if(raydir_x < 0)
	{
		game->ray.step_x = -1;
		game->player.side_distx = (game->player.pos_x - game->ray.map_x) * game->ray.delta_distx;
	}
	else
	{
		game->ray.step_x = 1;
		game->player.side_distx = (game->ray.map_x + 1.0 - game->player.pos_x) * game->ray.delta_distx;
	}
	if(raydir_y < 0)
	{
		game->ray.step_y = -1;
		game->player.side_disty = (game->player.pos_y - game->ray.map_y) * game->ray.delta_disty;
	}
	else
	{
		game->ray.step_y = 1;
		game->player.side_disty = (game->ray.map_y + 1.0 - game->player.pos_y) * game->ray.delta_disty;
	}
}

static void choose_textr(t_game *game, double raydir_x, double raydir_y, int x)
{
	if(game->player.side == 0)
		game->player.to_wall = (game->ray.map_x - game->player.pos_x + (1 - game->ray.step_x) / 2) / raydir_x;
	else
		game->player.to_wall = (game->ray.map_y - game->player.pos_y + (1 - game->ray.step_y) / 2) / raydir_y;
	if (game->sprites.amount_sprt > 0)
		game->z_buff[x] = game->player.to_wall;
	game->ray.line_height = (int)(game->mlx.win_width / game->player.to_wall);
	if (game->player.side == 1 && game->ray.step_y < 0)
		game->txtr.current = game->txtr.wall_n;
	else if (game->player.side == 1 && game->ray.step_y > 0)
		game->txtr.current = game->txtr.wall_s;
	else if (game->player.side == 0 && game->ray.step_x < 0)
		game->txtr.current = game->txtr.wall_e;
	else if (game->player.side == 0 && game->ray.step_x > 0)
		game->txtr.current = game->txtr.wall_w;
	if (game->map.map[game->ray.map_y][game->ray.map_x] == '2')
		game->txtr.current = game->txtr.sprite;
}

static void dda_perform(t_game *game, double raydir_x, double raydir_y, int x)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if(game->player.side_distx < game->player.side_disty)
		{
			game->player.side_distx += game->ray.delta_distx;
			game->ray.map_x += game->ray.step_x;
			game->player.side = 0;
		}
		else
		{
			game->player.side_disty += game->ray.delta_disty;
			game->ray.map_y += game->ray.step_y;
			game->player.side = 1;
		}
		if(game->map.map[game->ray.map_y][game->ray.map_x] == '1')
			hit = 1;
	}
	choose_textr(game, raydir_x, raydir_y, x);
}

static void calculate_txtr_pos(t_game *game, int x, double raydir_x, double raydir_y)
{
	game->ray.draw_start = -game->ray.line_height / 2 + game->mlx.win_hight / 2;
	if(game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + game->mlx.win_hight / 2;
	if(game->ray.draw_end >= game->mlx.win_hight)
		game->ray.draw_end = game->mlx.win_hight - 1;
	if (game->player.side == 0)
		game->txtr.wall_x = game->player.pos_y + game->player.to_wall * raydir_y;
	else
		game->txtr.wall_x = game->player.pos_x + game->player.to_wall * raydir_x;
	game->txtr.wall_x -= floor(game->txtr.wall_x);
	game->txtr.tex_x = (int)(game->txtr.wall_x * (double)TEXWIDTH);
	game->txtr.step = 1.0 * TEXHEIGHT / game->ray.line_height;
	game->txtr.tex_pos = (game->ray.draw_start - game->mlx.win_hight / 2.0 + \
		game->ray.line_height / 2.0) * game->txtr.step;
	while(game->ray.draw_start < game->ray.draw_end)
	{
		game->txtr.tex_y = (int)game->txtr.tex_pos & (TEXHEIGHT - 1);
		game->txtr.tex_pos += game->txtr.step;
		game->txtr.color = ft_get_pxl_clr(game->txtr.current, game->txtr.tex_x, game->txtr.tex_y);
		my_mlx_pixel_put(game->data, x, game->ray.draw_start, game->txtr.color);
		game->ray.draw_start++;
	}
}

void print_ray(t_game *game)
{
	int x;
	double cameraX;
	double raydir_x;
	double raydir_y;

	x = 0;
	while (x < game->mlx.win_width)
	{
		game->current_x = x;
		cameraX = 2 * x / (double)game->mlx.win_width - 1;  
		raydir_x = game->player.dir_x + game->player.plane_x * cameraX;
		raydir_y = game->player.dir_y + game->player.plane_y * cameraX;

		game->ray.map_x = (int)(game->player.pos_x);
		game->ray.map_y = (int)(game->player.pos_y);

		if (raydir_y != 0)
			if (raydir_x != 0)
				game->ray.delta_distx = fabs(1 / raydir_x);
		if (raydir_x != 0)
			if (raydir_y != 0)
				game->ray.delta_disty = fabs(1 / raydir_y);
				
		side_step(game, raydir_x, raydir_y);
		dda_perform(game, raydir_x, raydir_y, x);
		calculate_txtr_pos(game, x, raydir_x, raydir_y);
		x++;
	}
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
