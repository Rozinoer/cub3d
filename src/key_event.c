/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:17:03 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:17:05 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void another_key(int keycode, t_game *game, double olddir_x, double oldplane_x)
{
	double rotSpeed;

	rotSpeed = 0.1;
	if (keycode == 123)
		rotSpeed *= -1;
	else if (keycode == 53)
	{
		mlx_destroy_image(game->mlx.mlx, game->data.img);
		mlx_clear_window(game->mlx.mlx, game->mlx.mlx_win);
		mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
		exit(0);
	}
	game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed);
	game->player.dir_y = olddir_x * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);
	game->player.plane_x = game->player.plane_x * cos(rotSpeed) - game->player.plane_y * sin(rotSpeed);
	game->player.plane_y = oldplane_x * sin(rotSpeed) + game->player.plane_y * cos(rotSpeed);
	render_next_frame(game);
}

static void forward_reverse(int keycode, t_game *game)
{
	double move_speed;
	double smooth;

	smooth = 0.1;
	move_speed = 0.1;
	if (keycode == S)
	{
		move_speed *= -1;
		smooth *= -1;
	}
	if (game->map.map[(int)(game->player.pos_y + game->player.dir_y * (move_speed + smooth))]
	[(int)(game->player.pos_x + game->player.dir_x * (move_speed + smooth))] != '1')
	{
		game->player.pos_x += game->player.dir_x * move_speed;
		game->player.pos_y += game->player.dir_y * move_speed;
		render_next_frame(game);
	}
}

static void left_right(int keycode, t_game *game)
{
	double move_speed;
	double smooth;

	smooth = 0.5;
	move_speed = 0.1;
	if (keycode == A)
	{
		move_speed *= -1;
		smooth *= -1;
	}
	if (game->map.map[(int)(game->player.pos_y + game->player.dir_y * (move_speed * game->player.plane_y))]
	[(int)(game->player.pos_x - game->player.dir_x * (move_speed * game->player.plane_x))] != '1')
	{
		game->player.pos_y -= -game->player.dir_x * move_speed;
		game->player.pos_x -= game->player.dir_y * move_speed;
		render_next_frame(game);
	}
}

int key_pressed(int keycode, t_game *game)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = game->player.dir_x;
	oldplane_x = game->player.plane_x;
	if (keycode == W || keycode == S)
	{
		forward_reverse(keycode, game);
	}
	if (keycode == A || keycode == D)
	{
		left_right(keycode, game);
	}
	else if (keycode == 124 || keycode == 123 || keycode == 53)
		another_key(keycode, game, olddir_x, oldplane_x);
	return(0);
}
